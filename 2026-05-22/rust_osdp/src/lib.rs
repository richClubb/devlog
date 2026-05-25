
use std::fmt::Error;

const SOM_POS: usize = 0x00;
const SOM_VALUE: u8 = 0x53;
const ADDR_POS: usize = 0x01;
const LEN_LSB_POS: usize = 0x02;
const LEN_MSB_POS: usize = 0x03;

const CTRL_POS: usize = 0x04;
const CTRL_CHKSUM_FLAG_MASK: usize = 0x04;

// for secure messages
const SEC_BLK_LEN_POS: usize = 0x05;
const SEC_BLK_TYPE_POS: usize = 0x06;
const SEC_BLK_DATA_START_POS: usize = 0x07;
// As secure messages data len can be unknown we don't know the pos of the rest of the info
// The command byte is offset from the end of the SEC_BLK_DATA end
const SEC_MSG_COMMAND_POS_OFFSET: usize = 0x01;
const SEC_MSG_DATA_START_POS: usize = 0x02;
// the MAC Is offset from the end of the data section
const SEC_MSG_MAC_POS_OFFSET: usize = 0x01;
const SEC_MSG_CRC_CHECKSUM_OFFSET: usize = 0x05;

// for non-secure messages
const NON_SEC_MSG_COMMAND_POS: usize = 0x05;
const NON_SEC_MSG_DATA_START_POS: usize = 0x06;
const NON_SEC_MSG_CRC_CHECKSUM_OFFSET: usize = 0x01;

enum OsdpMessageChecksumType {
    CHECKSUM,
    CRC
}

use std::os::raw::{
    c_uchar,
    c_ulong
};

#[repr(C)]
#[derive(Clone)]
pub struct OsdpFuncHandler {
    function: fn(&OsdpMessage) -> OsdpMessage,
    command_id: u8,
}

#[repr(C)]
pub struct OsdpMessage {
    addr: u8,
    length: u16,
    ctrl: u8,
    sec_blk_len: u8,
    sec_blk_type: u8,
    //sec_blk_data: Vec<u8>,
    cmnd: u8,
    //data: Vec<u8>,
    mac: u32
}

impl OsdpMessage {

    fn get_length(payload: &Vec<u8>) -> u16 {
        let mut result: u16 = ((payload[LEN_MSB_POS] as u16) << 0x08) as u16;
        result += payload[LEN_LSB_POS] as u16;
        return result;
    } 

    fn is_secure_message(ctrl_val: &u8) -> bool {

        let secure_bit = ctrl_val & 0x08 >> 3;

        if secure_bit == 1 {
            return true;
        }
        return false;
    }

    // Requires the payload to have been validated correctly.
    pub fn from_u8_payload(payload: &Vec<u8>) -> OsdpMessage{
        let length = OsdpMessage::get_length(payload);
        let ctrl = payload[CTRL_POS];
        
        if OsdpMessage::is_secure_message(&ctrl) {
            let sec_blk_len = payload[SEC_BLK_LEN_POS];
            let sec_blk_type = payload[SEC_BLK_TYPE_POS];
            let command = 0;
            let mac: u32 = 0;

            return OsdpMessage { addr: 0, length: length, ctrl: ctrl, sec_blk_len: sec_blk_len, sec_blk_type: sec_blk_type, cmnd: command, mac: mac};
        }
        else {
            let command = payload[NON_SEC_MSG_COMMAND_POS]; 

            return OsdpMessage { addr: 0, length: length, ctrl: ctrl, sec_blk_len: 0, sec_blk_type: 0, cmnd: command, mac: 0};
        }
    }

    pub fn to_u8_payload(&self) {

    }
}


#[repr(C)]
pub struct OsdpEngine {
    // guid: String,
    id: u8,
    processing_multiframe: bool,
    last_sequence: u8,
    handler_functions: *const OsdpFuncHandler,
    handler_functions_size: u8,
    nack_handler_function: fn(&OsdpMessage) -> OsdpMessage
}

impl OsdpEngine {
    pub fn process_osdp_message(&self, osdp_message: OsdpMessage) -> Result<OsdpMessage, Error> {
        let handler_fn: fn(&OsdpMessage) -> OsdpMessage = self.get_handler_fn(osdp_message.cmnd);

        // Ok(OsdpMessage { addr: 0, length: 0, ctrl: 0, sec_blk_len: 0, sec_blk_type: 0, sec_blk_data: vec![0; 1], cmnd: 0, data: vec![0; 1], mac: 0})
        Ok(handler_fn(&osdp_message))
    }

    fn get_handler_fn(&self, command: u8) -> fn(&OsdpMessage) -> OsdpMessage {

        println!("Command: {}", command);
        for index in 0..self.handler_functions_size {
            unsafe {
                let command_handler = self.handler_functions.offset(index as isize).clone();
                if (*command_handler).command_id == command {
                    return (*command_handler).function;
                }
            }
        }

        println!("Unrecongised command");
        return self.nack_handler_function;
    }
}

fn get_checksum_type(payload: &Vec<u8>) -> OsdpMessageChecksumType {
    let chksum_bit = (payload[CTRL_POS] & (CTRL_CHKSUM_FLAG_MASK as u8)) >> 2;

    if chksum_bit == 0x01 {
        return OsdpMessageChecksumType::CRC
    }

    return OsdpMessageChecksumType::CHECKSUM;
}

fn extract_checksum(payload: &Vec<u8>) -> u16 {
    let checksum = payload.last().unwrap();
    return checksum.clone() as u16;
}

fn extract_crc(payload: &Vec<u8>) -> u16 {
    return 0;
}

fn calculate_checksum(payload: &Vec<u8>) -> u16 {
    
    // this isn't correct need 2's compliment + 1
    let mut result:usize = 0;
    for index in 0..payload.len() - 1 {
        result += payload[index] as usize;
    }
    return (result & 0xff) as u16;
}

fn calculate_crc(payload: &Vec<u8>) -> u16 {
    return 0;
}


fn validate_message_checksum(payload: &Vec<u8>) -> bool {

    // get type of checksum
    let checksum_type = get_checksum_type(payload);

    let message_checksum = match checksum_type {
        OsdpMessageChecksumType::CHECKSUM => extract_checksum(payload),
        OsdpMessageChecksumType::CRC => extract_crc(payload),
    };

    let calculated_checksum = match checksum_type {
        OsdpMessageChecksumType::CHECKSUM => calculate_checksum(payload),
        OsdpMessageChecksumType::CRC => calculate_crc(payload),
    };

    if message_checksum != calculated_checksum {
        return false;
    }

    return true;
}

/* 
    Purpose: Processes the message and produces the response
    Side Effects: Will call any of the associated command functions
*/
fn process_osdp_message(osdp_message: OsdpMessage) -> Result<OsdpMessage, Error> {

    // Ok(OsdpMessage { addr: 0, length: 0, ctrl: 0, sec_blk_len: 0, sec_blk_type: 0, sec_blk_data: vec![0 ; 1], cmnd: 0, data: vec![0; 1], mac: 0 })
    Ok(OsdpMessage { addr: 0, length: 0, ctrl: 0, sec_blk_len: 0, sec_blk_type: 0, cmnd: 0, mac: 0})
}


#[unsafe(no_mangle)]
pub extern "C" fn process_payload(context: OsdpEngine, data: *const c_uchar, size: c_ulong) -> bool {

    let mut payload: Vec<u8> = vec![0; size as usize];

    // extract the data into a payload
    unsafe {    
        let mut offset: isize = -1;
        for index in 0..(size as usize) {
            let val = *data.offset(index as isize) as u8;

            if (val == SOM_VALUE) && (offset == -1) {
                offset = index as isize;
            }

            payload[(index as isize - offset) as usize] = val;
        }
    }
    
    // verify ID (we can't process the message unless it's for us)
    if payload[ADDR_POS] != context.id {
        println!("Invalid address");
        return false;
    }

    // // verify the message (check checksums)
    // if !validate_message_checksum( &payload ) {
    //     println!("Invalid checksum");
    //     return false;
    // }

    let osdp_message = OsdpMessage::from_u8_payload(&payload);

    let _ = context.process_osdp_message(osdp_message);

    return true;
}

pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}

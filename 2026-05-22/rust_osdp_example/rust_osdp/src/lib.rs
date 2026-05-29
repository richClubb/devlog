
use std::fmt::Error;
use std::ptr::null;

pub mod checksum_crc;

const OSDP_PAYLOAD_MIN_LENGTH: usize = 7;
const OSDP_PAYLOAD_MAX_LENGTH: usize = 1440;

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

#[derive(Debug, PartialEq)]
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
    // Would rather these be vectors
    sec_blk_data_ptr: *const u8,
    sec_blk_data_ptr_size: u16,
    //sec_blk_data: Vec<u8>,
    cmnd: u8,
    // Would rather these be vectors
    data_ptr: *const u8,
    data_ptr_size: u32,
    //data: Vec<u8>,
    mac: u32
}

impl OsdpMessage {

    fn empty() -> OsdpMessage {
        return OsdpMessage { 
            addr: 0, 
            length: 0, 
            ctrl: 0, 
            sec_blk_len: 0, 
            sec_blk_type: 0, 
            sec_blk_data_ptr: null(), 
            sec_blk_data_ptr_size: 0, 
            cmnd: 0, 
            data_ptr: null(), 
            data_ptr_size: 0, 
            mac: 0
        };
    }

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

    fn secure_msg_from_u8_payload(_: &Vec<u8>) -> OsdpMessage {
        // let length = OsdpMessage::get_length(payload);
        // let ctrl = payload[CTRL_POS];
        // let sec_blk_len = payload[SEC_BLK_LEN_POS];
        // let sec_blk_type = payload[SEC_BLK_TYPE_POS];
        // let command = 0;
        // let mac: u32 = 0;

        return OsdpMessage::empty();
    }

    fn non_secure_msg_from_u8_payload(_: &Vec<u8>) -> OsdpMessage {
        // let command = payload[NON_SEC_MSG_COMMAND_POS]; 
        // let length = OsdpMessage::get_length(payload);
        // let ctrl = payload[CTRL_POS];

        return OsdpMessage::empty();
    }

    fn get_checksum_type(payload: &Vec<u8>) -> OsdpMessageChecksumType {
        let chksum_bit = (payload[CTRL_POS] & (CTRL_CHKSUM_FLAG_MASK as u8)) >> 2;

        if chksum_bit == 0x01 {
            return OsdpMessageChecksumType::CRC
        }

        return OsdpMessageChecksumType::CHECKSUM;
    }

    fn extract_checksum(payload: &Vec<u8>) -> u16 {
        let size = payload.len();
        return payload[size-1] as u16;
    }

    fn extract_crc(payload: &Vec<u8>) -> u16 {
        let size = payload.len();
        let crc = ((payload[size-2] as u16) << 8) | payload[size - 1] as u16;
        return crc;
    }

    fn validate_message_checksum(payload: &Vec<u8>) -> bool {

        // get type of checksum
        let checksum_type = OsdpMessage::get_checksum_type(payload);

        let message_checksum = match checksum_type {
            OsdpMessageChecksumType::CHECKSUM => OsdpMessage::extract_checksum(payload),
            OsdpMessageChecksumType::CRC => OsdpMessage::extract_crc(payload),
        };

        let calculated_checksum = match checksum_type {
            OsdpMessageChecksumType::CHECKSUM => {
                let message = &payload[0..(payload.len()-1)];
                checksum_crc::checksum::calculate_checksum(&message.to_vec()) as u16
            },
            OsdpMessageChecksumType::CRC => {
                let message = &payload[0..(payload.len()-2)];
                checksum_crc::crc_fast::calculate_crc(&message.to_vec())
            },
        };

        if message_checksum != calculated_checksum {
            return false;
        }

        return true;
    }

    fn validate_length(payload: &Vec<u8>) -> bool {

        let payload_len = payload.len();
        if payload_len < OSDP_PAYLOAD_MIN_LENGTH {
            return false;
        }

        let length = OsdpMessage::get_length(payload);

        if payload_len != length as usize {
            return false;
        }

        if (length as usize) > OSDP_PAYLOAD_MAX_LENGTH {
            return false;
        } 

        return true;
    }

    pub fn validate_payload(payload: &Vec<u8>) -> bool {

        if !OsdpMessage::validate_length(payload) {
            return false;
        }

        if payload[SOM_POS] != SOM_VALUE {
            return false;
        }

        if !OsdpMessage::validate_message_checksum(payload) {
            return false;
        }
        
        return true;
    }

    // Requires the payload to have been validated correctly.
    pub fn from_u8_payload(payload: &Vec<u8>) -> Result<OsdpMessage, Error>{
        
        // validate payload
        let _ = OsdpMessage::validate_payload(payload);
        
        let ctrl = payload[CTRL_POS];
        
        if OsdpMessage::is_secure_message(&ctrl) {
            return Ok(OsdpMessage::secure_msg_from_u8_payload(payload))
        }
        else {
            return Ok(OsdpMessage::non_secure_msg_from_u8_payload(payload))
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
    nack_handler_function: fn(&OsdpMessage) -> OsdpMessage,
    decode_message_function: fn(&OsdpMessage) -> OsdpMessage
}

impl OsdpEngine {
    pub fn process_osdp_message(&self, osdp_message: OsdpMessage) -> Result<OsdpMessage, Error> {
        let handler_fn: fn(&OsdpMessage) -> OsdpMessage = self.get_handler_fn(osdp_message.cmnd);

        // Ok(OsdpMessage { addr: 0, length: 0, ctrl: 0, sec_blk_len: 0, sec_blk_type: 0, sec_blk_data: vec![0; 1], cmnd: 0, data: vec![0; 1], mac: 0})
        Ok(handler_fn(&osdp_message))
    }

    pub fn process_osdp_message_c(&self, osdp_message: OsdpMessage) -> Result<OsdpMessage, Error> {
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

// /* 
//     Purpose: Processes the message and produces the response
//     Side Effects: Will call any of the associated command functions
// */
// fn process_osdp_message(osdp_message: OsdpMessage) -> Result<OsdpMessage, Error> {

//     // Ok(OsdpMessage { addr: 0, length: 0, ctrl: 0, sec_blk_len: 0, sec_blk_type: 0, sec_blk_data: vec![0 ; 1], cmnd: 0, data: vec![0; 1], mac: 0 })
//     Ok(OsdpMessage::empty())
// }


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

    let osdp_message = OsdpMessage::from_u8_payload(&payload);
    match osdp_message {
        Ok(result) => {
            let _ = context.process_osdp_message(result);
        },
        Err(_) => println!("Error"),
    }

    return true;
}

pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_checksum_type_crc_1() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x60];
        let result = OsdpMessage::get_checksum_type(&input);
        assert_eq!(OsdpMessageChecksumType::CRC, result);
    }

    #[test]
    fn test_get_checksum_type_crc_2() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x60];
        let result = OsdpMessage::get_checksum_type(&input);
        assert_eq!(OsdpMessageChecksumType::CRC, result);
    }

    #[test]
    fn test_get_checksum_type_crc_3() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x60];
        let result = OsdpMessage::get_checksum_type(&input);
        assert_eq!(OsdpMessageChecksumType::CRC, result);
    }

    #[test]
    fn test_get_checksum_type_checksum() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x00, 0x60];
        let result = OsdpMessage::get_checksum_type(&input);
        assert_eq!(OsdpMessageChecksumType::CHECKSUM, result);
    }

    #[test]
    fn test_validate_payload_1_too_short() {
        let input: Vec<u8> = vec![0x53];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(false, result);
    }

    #[test]
    fn test_validate_payload_2_valid_checksum() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x07, 0x00, 0x00, 0x60, 0x46];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(true, result);
    }

    #[test]
    fn test_validate_payload_3_invalid_checksum() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x07, 0x00, 0x00, 0x60, 0x45];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(false, result);
    }

    #[test]
    fn test_validate_payload_4_correct_crc() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x60, 0xAA, 0xEB];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(true, result);
    }

    #[test]
    fn test_validate_payload_5_invalid_crc() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x60, 0xAA, 0xEC];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(false, result);
    }

    #[test]
    fn test_validate_payload_6_invalid_data_crc_check() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x61, 0xAA, 0xEB];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(false, result);
    }

    #[test]
    fn test_validate_payload_7_invalid_length_too_long() {
        let input: Vec<u8> = vec![0; 1441];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(false, result);
    }

    #[test]
    fn test_validate_payload_8_invalid_start_of_message() {
        let input: Vec<u8> = vec![0x50, 0x00, 0x07, 0x00, 0x00, 0x60, 0x46];
        let result = OsdpMessage::validate_payload(&input);
        assert_eq!(false, result);
    }
}



pub fn calculate_crc(payload: &Vec<u8>) -> u16 {
    
    let mut n_crc: u16 = 0x1D0F;
    for value in payload {
        n_crc = (n_crc >> 8) | (n_crc << 8);
        n_crc ^= (*value) as u16;
        n_crc ^= (n_crc & 0xff) >> 4;
        n_crc ^= (n_crc << 8) << 4;
        n_crc ^= ((n_crc & 0xff) << 4) << 1;
    }
    
    return n_crc;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_calculate_crc_1() {
        let input: Vec<u8> = vec![1, 2, 3, 4];
        let expected_result: u16 = 0x313;

        let calculated_result = calculate_crc(&input);
        assert_eq!(calculated_result, expected_result);
    }

    #[test]
    fn test_calculate_crc_2() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x08, 0x00, 0x04, 0x60];
        let expected_result: u16 = 0xAAEB;

        let calculated_result = calculate_crc(&input);
        assert_eq!(calculated_result, expected_result);
    }
}
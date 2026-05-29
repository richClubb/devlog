
pub fn calculate_checksum(payload: &Vec<u8>) -> u8 {
    let mut result: u8 = 0;
    for val in payload {
        result = result.wrapping_add(*val);
    }
    
    // 2s compliment + 1
    result = !result;
    return result.wrapping_add(1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_calculate_checksum_1() {
        let input: Vec<u8> = vec![1, 2, 3, 4];
        let expected_result = 246;

        let calculated_result = calculate_checksum(&input);
        assert_eq!(calculated_result, expected_result);
    }

    #[test]
    fn test_calculate_checksum_2() {
        let input: Vec<u8> = vec![0xff, 0xfe, 0xfd, 0xfc];
        let expected_result = 0xa;

        let calculated_result = calculate_checksum(&input);
        assert_eq!(calculated_result, expected_result);
    }

    #[test]
    fn test_calculate_checksum_3() {
        let input: Vec<u8> = vec![0x53, 0x00, 0x07, 0x00, 0x00, 0x60];
        let expected_result = 0x46;

        let calculated_result = calculate_checksum(&input);
        assert_eq!(calculated_result, expected_result);
    }
}
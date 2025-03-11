pub fn add(left: u8, right: u8) -> u8 {
    
    if (std::u8::MAX - left) < right {
        return std::u8::MAX;
    }

    left + right
}

pub fn sub(left: u8, right: u8) -> u8 {
    
    if (std::u8::MAX - right) < left {
        return std::u8::MIN;
    }
    left - right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add_basic() {
        assert_eq!(add(1, 2), 3);
    }

    #[test]
    fn test_add_close_boundary() {
        assert_eq!(add(253, 1), 254);
    }

    #[test]
    fn test_add_at_boundary() {
        assert_eq!(add(254, 1), 255);
    }

    #[test]
    fn test_add_over_boundary() {
        assert_eq!(add(255, 1), 255);
    }

    #[test]
    fn test_add_max() {
        assert_eq!(add(std::u8::MAX, std::u8::MAX), 255);
    }
    
    #[test]
    fn test_sub_basic() {
        assert_eq!(sub(4, 1), 3);
    }

    #[test]
    fn test_sub_close_boundary() {
        assert_eq!(sub(4, 3), 1);
    }

    #[test]
    fn test_sub_at_boundary() {
        assert_eq!(sub(4, 4), 0);
    }

    #[test]
    fn test_sub_over_boundary() {
        assert_eq!(sub(4, 5), 0);
    }

    #[test]
    fn test_sub_min() {
        assert_eq!(sub(std::u8::MIN, std::u8::MAX), 0);
    }
}

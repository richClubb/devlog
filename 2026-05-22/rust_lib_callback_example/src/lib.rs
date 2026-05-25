use std::os::raw::c_int;

pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[unsafe(no_mangle)]
pub extern "C" fn a_rust_function() -> bool {
    println!("in the rust function");
    true
}

type CallbackCInt = fn() -> c_int;

type CallbackBool = fn() -> bool;

fn dummy() -> c_int {
    return 0x5a;
}

#[repr(C)]
pub struct ALibObject {
    a_thing_1: CallbackCInt,
    a_thing_2: CallbackCInt,
    check_func: CallbackBool,
}

impl ALibObject {
    pub fn check(&self) -> bool {
        if (self.check_func)() {
            return true;
        }

        return false;
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn init_lib() -> ALibObject {
    
    let result =ALibObject { 
        a_thing_1: || {
            1
        }, 
        a_thing_2: || {
            2
        },
        check_func: || {
            true
        }
    };

    return result;
}

#[unsafe(no_mangle)]
pub extern "C" fn process(obj: ALibObject) -> c_int {
    if (obj.check_func)() {
        return 7
    }

    return 9;
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn test_a_rust_function() {
        assert_eq!(true, a_rust_function());
    }
}

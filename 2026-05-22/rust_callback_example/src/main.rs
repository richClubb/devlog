use libc::c_int;

#[link(name = "a_lib")]
unsafe extern "C" {
    pub safe fn a_function() -> c_int;
}

fn a_function_wrapper() -> i64 {
    let result = a_function();
    return i64::from(result);
}

type Callback = fn() -> i64;

fn main() {
    println!("Hello, world!");

    let thing: Callback;
    thing = a_function_wrapper; 

    println!("{}", a_function());
    println!("{}", a_function());

    println!("{}", thing());
    println!("{}", thing());
}

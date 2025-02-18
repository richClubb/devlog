use string_extension::NewLength;

mod string_extension;

fn main() {
    println!("Hello, world!");

    let a_string = String::from("This is a test!");
    let new_len = a_string.new_len();
    println!("The new len is {new_len}");
}

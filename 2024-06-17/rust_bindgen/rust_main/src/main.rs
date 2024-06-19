mod bindings;
mod foo;
use crate::bindings::add;

fn main() {
    println!("Hello, world!");

    unsafe {
        let result = add(1, 40);
        println!("Result {result}");
    }

    foo::foo();
}

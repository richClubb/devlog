fn foo(value: usize) -> usize {
    value + 1
}

fn main() {

    let example_closure = |a| {foo(a)};

    let x = 1;
    let y = foo(x);
    let z = example_closure(y);
    let b = (|c| {foo(c)})(z);
    println!{"{}, {}, {}, {}", x, y, z, b};
}
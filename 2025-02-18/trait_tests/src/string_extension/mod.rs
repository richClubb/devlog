

pub trait NewLength {
    fn new_len(&self) -> usize;
}

impl NewLength for String {
    fn new_len(&self) -> usize{
        println!("using an extension trait");
        return self.len()
    }
}
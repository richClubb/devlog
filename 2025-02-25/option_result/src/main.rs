use std::io::{Error, ErrorKind};

fn result_function(number: usize) -> Result<usize, std::io::Error> {
    
    if number > 5 {
        return Err(Error::new(ErrorKind::Other,"Number too large"));
    }
      
    Ok(number)
}

fn wrap_result(number: usize) -> Result<usize, std::io::Error> {
    let x = result_function(number)?;

    Ok(x)
}


fn option_function(number: usize) -> Option<usize> {

    if number > 5 {
        return None;
    }

    Some(number)
}

fn wrap_option(number: usize) -> Option<usize> {
    let x = option_function(number)?;

    Some(x)
}

fn main() {
    println!("Testing options and results");

    let x = option_function(4);
    match x {
        Some(value) => println!("Value is: {value}"),
        None => println!("No value")
    }
    
    let x = option_function(6);
    match x {
        Some(value) => println!("Value is: {value}"),
        None => println!("No value")
    }
    
    let x = result_function(4);
    match x {
        Ok(value) => println!("Value is: {value}"),
        Err(error) => println!("Error is: {error}")
    }

    let x = result_function(6);
    match x {
        Ok(value) => println!("Value is: {value}"),
        Err(error) => println!("Error is: {error}")
    }

    let x = |number| -> usize  {option_function(number).unwrap_or(0) + result_function(number).unwrap_or(0)}(6);
    println!("{x}");

    let number = 6;
    let x = option_function(number).ok_or("Number to big");
}

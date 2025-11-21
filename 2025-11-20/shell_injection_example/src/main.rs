#[macro_use] extern crate rocket;
use std::process::{Command, ExitStatus};

#[get("/")]
fn index() -> &'static str {
    "Hello, world!"
}

#[post("/hellouser", data="<user>")]
fn hello_user(user: Option<&str>) -> String {
    match user {
        Some(x) => {
            let mut check_user_cmd = Command::new("sh");
            check_user_cmd.arg("-c").arg(format!("id {0}", x));
            let resp = check_user_cmd.output().expect("failed to execute process");
            if resp.status.success() {
                return format!("Hello {0}", x);
            }
            else {
                return format!("No user with that name");
            }

        },
        None => return format!("No user specified"),
    }
}

#[post("/adduser", data="<user>")]
fn add_user(user: Option<&str>) -> String {
    match user {
        Some(x) => {
            let mut add_user_cmd = Command::new("/bin/bash");
            add_user_cmd.arg("-c").arg(format!("sudo useradd {0}", x));
            println!("{x}");
            let resp = add_user_cmd.output().expect("failed to execute process");
            if resp.status.success() {
                return format!("Added user {0}", x);
            }
            else {
                return format!("Failed to add user");
            }
        },
        None => return format!("No user specified"),
    }
}

#[post("/deluser", data="<user>")]
fn del_user(user: Option<&str>) -> String {
    match user {
        Some(x) => {
            let mut del_user_cmd = Command::new("sh");
            del_user_cmd.arg("-c").arg(format!("sudo userdel {0}", x));
            let resp = del_user_cmd.output().expect("failed to execute process");
            if resp.status.success() {
                return format!("Deleted user {0}", x);
            }
            else {
                return format!("Failed to del user");
            }
        },
        None => return format!("No user specified"),
    }
}

#[launch]
fn rocket() -> _ {
    rocket::build().mount("/", routes![index, hello_user, add_user, del_user])
}
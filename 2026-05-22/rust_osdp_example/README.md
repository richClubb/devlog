# Rust OSDP

An example of how to do C and Rust interop.

The main logic behind the OSDP decoding / processing is done in Rust but it allows a user to implement the "handler" functions in C.

The `rust_osdp` folder is the main logic, but the `c_rust_osdp` folder contains C code which initially calls the rust code and sets up the function handlers that can use the payloads.


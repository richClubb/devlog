# Notes

## Building the headers

the `bindgen.toml` file needs to exist but it can be blank

`cbindgen -l c --config cbindgen.toml --crate rust_osdp --output rust_osdp.h` 


# General Links

https://rust-lang.github.io/rust-bindgen/requirements.html

https://makori-mildred.medium.com/how-to-create-a-dynamic-library-in-c-and-how-to-use-it-30c304f399a4

https://cmakebyexample.dev/add-include-folder/

# Notes

## Dynamic library creation

export LD_LIBRARY_PATH=:lib/ is necessary for the C code to know where the libs are located if they are in a non standard location

otherwise you can copy it into a standard library path e.g. `/usr/lib` errors like `./add_lib_dyn: error while loading shared libraries: lib_add_lib.so: cannot open shared object file: No such file or directory` result in not doing this or having an invalid path.

in the example I've been trying out the commands are 

```c
gcc -o lib/lib_add_lib.so -I includes/ src/add_lib.c -shared -fPIC
```

this can also be done in two steps

```c
gcc -c -o lib/add_lib.o src/add_lib.c -I includes/
gcc -shared lib/add_lib.o lib/lib_add_lib.so
```

the -fPIC is not "necessary" but I don't understand the not using it.

https://stackoverflow.com/questions/966960/what-does-fpic-mean-when-building-a-shared-library

Notes that PIC is "Position Independent Code" which has certain uses. With this example I tested it without and it did work.

```c
gcc -o add_lib_dyn main.c -I includes/ -L lib/ -l _add_lib
```

was used to compile the main code

## Static lib creation

it's really similar to the dynamic but you have a few different steps.

```c
gcc -c -o add_lib.o src/add_lib.c -I includes
ar rcs lib/lib_add_lib.a lib/add_lib.a
```

The `ar` command is `ar rcs [target] [src]`

```c
gcc -o add_lib_static main.c -L lib/ -I includes/ -l _add_lib
```

creates the static lib.

## CMake Notes

https://cmake.org/cmake/help/latest/guide/tutorial/Adding%20a%20Library.html

This is a note on how you should be arranging your files / libraries. It's a bit of an odd one considering how you might want to build separate parts of your solution and if they share code.ls

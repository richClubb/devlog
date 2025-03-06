# C Main

## Building

Currently builds with `cmake`. Starting from the `c_main` directory
```
mkdir build
cmake ../
make
```

## Running

From the build directory
```
./c_int_math
```

## Manual Build

```
gcc -o c_main main.c -I ../c_lib/include -I ../../cpp/cpp_lib/include/ -L ../c_lib/lib -L ../../cpp/cpp_lib/lib -l c_int_math_lib -l cpp_int_math_lib
```
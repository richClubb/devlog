# C++ lib

this is creating a C++ library that will be consumed by other languages

# Building

## Cmake Build

```
mkdir build
cd build
cmake ../
make
```

This will also make the unit tests

## Manual Build

execute from the root of te `cpp_lib` directory.

```
g++ -c -o lib.o src/cpp_int_math.cpp -I include -L lib -l cpp_int_math_lib
ar rcs libcpp_int_math_lib.a lib.o 
```

## Manually Build Tests

```
gcc -o test_c_int_math test_c_int_math_lib.c -I ../../include/ -L ../../lib -L /usr/lib/x
86_64-linux-gnu/ -l c_int_math_lib -l cunit
```
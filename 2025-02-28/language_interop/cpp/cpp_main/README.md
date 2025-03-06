## Building

## Building

Currently builds with `cmake`. Starting from the `cpp_main` directory
```
mkdir build
cmake ../
make
```

## Running

From the build directory
```
./cpp_int_math
```

## Manual Build

```
g++ -o cpp_main main.cpp -I ../cpp_lib/include/ -I ../../c/c_lib/include -L ../cpp_lib/lib -L ../../c/c_lib/lib -l cpp_int_math_lib -l c_int_math_lib
```
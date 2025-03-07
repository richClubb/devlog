import ctypes
from pathlib import Path

if __name__ == "__main__":

    print("Python language interop\n")

    c_libname = Path("/home/richard/personal/devlog/2025-02-28/language_interop/c/c_lib/lib/libc_int_math_lib.so")
    c_lib = ctypes.CDLL(c_libname)

    cpp_libname = Path("/home/richard/personal/devlog/2025-02-28/language_interop/cpp/cpp_lib/lib/libcpp_int_math_lib.so")
    cpp_lib = ctypes.CDLL(cpp_libname)

    c_temp = c_lib.c_uint8_add(1, 2)
    print("Add using C: {}".format(c_temp))

    # Name mangling causes issues calling native C functions so you have to use extern'ed versions
    cpp_temp = cpp_lib.c_cpp_uint8_add(1, 2)
    print("Add using C++: {}".format(cpp_temp))

    print("add using C#: NOT IMPLEMENTED")

    print("add using Python: NOT IMPLEMENTED")

    print("add using Rust: NOT IMPLEMENTED")
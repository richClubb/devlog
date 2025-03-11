#!/bin/env python3

# dotnet imports
from clr_loader import get_coreclr
from pythonnet import set_runtime
rt = get_coreclr()
set_runtime(rt)
import clr

# c imports 
import ctypes
from pathlib import Path

# Python imports
from python_int_math import uint8

if __name__ == "__main__":

    print("Python language interop\n")

    c_libname = Path("/workspaces/devlog/2025-02-28/language_interop/c/c_lib/lib/libc_int_math_lib.so")
    c_lib = ctypes.CDLL(c_libname)

    cpp_libname = Path("/workspaces/devlog/2025-02-28/language_interop/cpp/cpp_lib/lib/libcpp_int_math_lib.so")
    cpp_lib = ctypes.CDLL(cpp_libname)

    c_temp = c_lib.c_uint8_add(1, 2)
    print("Add using C: {}".format(c_temp))

    # Name mangling causes issues calling native C functions so you have to use extern'ed versions
    cpp_temp = cpp_lib.c_cpp_uint8_add(1, 2)
    print("Add using C++: {}".format(cpp_temp))

    # The python environment needs the C# runtime installed. This might be true for a lot of the examples so it might be better
    # to have a devcontainer for the entire project
    clr.AddReference("/workspaces/devlog/2025-02-28/language_interop/csharp/external_libs/csharp_int_math_lib.dll")
    from csharp_int_math_lib import IntMath
    csharp_temp = IntMath.addByte(1, 2)
    print("add using C#: {}".format(csharp_temp))

    python_temp = uint8.uint8_add(1, 2)
    print("add using Python: {}".format(python_temp))

    print("add using Rust: NOT IMPLEMENTED")
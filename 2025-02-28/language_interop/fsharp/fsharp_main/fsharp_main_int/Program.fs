open System.Runtime.InteropServices


module InteropWithC = 
    [<DllImport(@"libc_int_math_lib.so", CallingConvention = CallingConvention.Cdecl)>]
    extern byte c_uint8_add(byte a, byte b)

module InteropWithCpp = 
    [<DllImport(@"libcpp_int_math_lib.so", CallingConvention = CallingConvention.Cdecl)>]
    extern byte c_cpp_uint8_add(byte a, byte b)

open csharp_int_math_lib;
open fsharp_int_math;

// For more information see https://aka.ms/fsharp-console-apps
printfn "F# Language Interop"

let c_temp = InteropWithC.c_uint8_add((byte)1, (byte)2)
printfn "Add using C: %d" c_temp

let cpp_temp = InteropWithCpp.c_cpp_uint8_add((byte)1, (byte)2)
printfn "Add using C++: %d" cpp_temp

let csharp_temp = csharp_int_math_lib.IntMath.addByte((byte)1, (byte)2)
printfn "Add using C#: %d" csharp_temp

printfn "Add using Python: NOT IMPLEMENTED"

printfn "Add using Rust: NOT IMPLEMENTED"

//let fsharp_temp = fsharp_int_math.IntMath.add(1, 2)
let fsharp_temp = 0
printfn "Add using F#: %d" fsharp_temp

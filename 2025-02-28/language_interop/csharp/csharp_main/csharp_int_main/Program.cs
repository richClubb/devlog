// See https://aka.ms/new-console-template for more information

using System.Runtime.InteropServices;

using CIntMathWrapper;
using CppIntMathWrapper;
using csharp_int_math_lib;
using fsharp_int_math;
using RustIntMathWrapper;

public class CSharpIntMath
{

    public static void Main(string[] args)
    {
        Console.WriteLine("C# Language Interop");
        // Using C
        byte c_int = CIntMath.c_uint8_add(1, 2);
        Console.WriteLine("Add using C: {0:D}", c_int);

        // Using C++
        byte cpp_int = CppIntMath.c_cpp_uint8_add(1, 2);
        Console.WriteLine("Add using C++: {0:D}", c_int);
        
        // Using C#
        byte csharp_int = csharp_int_math_lib.IntMath.addByte(1, 2);
        Console.WriteLine("add using C#: {0:D}", csharp_int);

        // Using Python
        Console.WriteLine("add using Python: NOT IMPLEMENTED");

        // Using Rust
        byte rust_int = RustIntMath.add(1, 2);
        Console.WriteLine("add using Rust: {0:D}", rust_int);

        // Using F#
        byte fsharp_int = (byte)fsharp_int_math.IntMath.add(1, 2);
        Console.WriteLine("add using F#: {0:D}", fsharp_int);
    }
}
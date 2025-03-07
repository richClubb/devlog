// See https://aka.ms/new-console-template for more information

using System.Runtime.InteropServices;

using CIntMathWrapper;
using CppIntMathWrapper;
using csharp_int_math_lib;

public class CSharpIntMath
{

    public static void Main(string[] args)
    {
        // Using C
        byte c_int = CIntMath.c_uint8_add(1, 2);
        Console.WriteLine("Add using C: {0:D}", c_int);

        // Using C++
        byte cpp_int = CppIntMath.c_cpp_uint8_add(1, 2);
        Console.WriteLine("Add using C++: {0:D}", c_int);
        
        // Using C#
        byte csharp_int = IntMath.addByte(1, 2);
        Console.WriteLine("add using C#: {0:D}", csharp_int);

        // Using Python
        Console.WriteLine("add using Python: NOT IMPLEMENTED");

        // Using Rust
        Console.WriteLine("add using Rust: NOT IMPLEMENTED");
    }
}
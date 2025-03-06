// See https://aka.ms/new-console-template for more information

using CIntMathWrapper;

public class CSharpIntMath
{
    public static void Main(string[] args)
    {
        // Using C
        byte temp = CIntMath.c_uint8_add(1, 2);
        Console.WriteLine("Add using C: ", temp);

        // Using C++
        Console.WriteLine("Add using C++: NOT IMPLEMENTED");
        
        // Using C#
        Console.WriteLine("add using C#: NOT IMPLEMENTED");

        // Using Python
        Console.WriteLine("add using Python: NOT IMPLEMENTED");

        // Using Rust
        Console.WriteLine("add using Rust: NOT IMPLEMENTED");
    }
}
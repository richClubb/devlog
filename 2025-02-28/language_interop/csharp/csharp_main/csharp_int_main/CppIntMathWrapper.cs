using System.Runtime.InteropServices;

namespace CppIntMathWrapper
{
    public static class CppIntMath{

        [DllImport("libcpp_int_math_lib.so")]
        public static extern byte c_cpp_uint8_add(byte a, byte b);

        [DllImport("libcpp_int_math_lib.so")]
        public static extern byte c_cpp_uint8_sub(byte a, byte b);
    }

}

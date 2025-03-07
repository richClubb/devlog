using System.Runtime.InteropServices;

namespace CIntMathWrapper
{
    public static class CIntMath{

        [DllImport("libc_int_math_lib.so")]
        public static extern byte c_uint8_add(byte a, byte b);

        [DllImport("libcpp_int_math_lib.so")]
        public static extern byte c_uint8_sub(byte a, byte b);

    }

}

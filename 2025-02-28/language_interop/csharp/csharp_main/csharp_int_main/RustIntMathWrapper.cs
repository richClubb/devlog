using System.Runtime.InteropServices;

namespace RustIntMathWrapper
{
    public static class RustIntMath{

        [DllImport("librust_int_math_lib.so")]
        public static extern byte add(byte a, byte b);

        [DllImport("librust_int_math_lib.so")]
        public static extern byte sub(byte a, byte b);
    }

}

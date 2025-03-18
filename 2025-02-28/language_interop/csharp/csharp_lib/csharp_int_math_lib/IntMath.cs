using System.Runtime.InteropServices;

namespace csharp_int_math_lib
{
    public static class IntMath
    {
       
        public static byte addByte(byte a, byte b)
        {
            int temp = a + b;
            if (temp > System.Byte.MaxValue) return System.Byte.MaxValue;
            return (byte)temp;
        }

        
        public static byte subtractByte(byte a, byte b)
        {
            int temp = a - b;
            if (temp < System.Byte.MinValue) return System.Byte.MinValue;
            return (byte)temp;
        }
    }
}

using csharp_int_math_lib;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace csharp_int_math_lib.test;

[TestClass]
public class IntMathTests
{
    [TestMethod]
    [DataRow(1, 2, 3)]
    [DataRow(2, 2, 4)]
    [DataRow(3, 2, 5)]
    [DataRow(4, 2, 6)]
    [DataRow(1, 6, 7)]

    public void addTests(int a, int b, int expected_result)
    {
        Assert.AreEqual(IntMath.addByte((byte)a, (byte)b), (byte)expected_result);
    }
}
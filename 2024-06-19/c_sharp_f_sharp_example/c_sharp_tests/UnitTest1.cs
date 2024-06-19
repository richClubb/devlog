namespace c_sharp_tests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            var test = new c_sharp.Class1();
            test.hello();
        }
    }
}
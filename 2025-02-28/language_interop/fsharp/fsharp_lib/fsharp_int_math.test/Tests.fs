namespace fsharp_int_math.test

open System
open Microsoft.VisualStudio.TestTools.UnitTesting

open fsharp_int_math

[<TestClass>]
type TestClass () =

    [<TestMethod>]
    member this.TestAdd () =
        let result = IntMath.add((byte)1, (byte)2)
        Assert.AreEqual((byte)3, result)

    [<TestMethod>]
    member this.TestAddNearBoundary () =
        let result = IntMath.add((byte)253, (byte)1)
        Assert.AreEqual((byte)254, result)

    [<TestMethod>]
    member this.TestAddAtBoundary () =
        let result = IntMath.add((byte)254, (byte)1)
        Assert.AreEqual((byte)255, result)

    [<TestMethod>]
    member this.TestAddOverBoundary () =
        let result = IntMath.add((byte)255, (byte)1)
        Assert.AreEqual((byte)255, result)

    [<TestMethod>]
    member this.TestEqual () =
        let result = IntMath.add((byte)127, (byte)127)
        Assert.AreEqual((byte)254, result)

    [<TestMethod>]
    member this.TestSub () =
        let result = IntMath.sub((byte)3, (byte)1)
        Assert.AreEqual((byte)2, result)

    [<TestMethod>]
    member this.TestSubNearBoundary () =
        let result = IntMath.sub((byte)3, (byte)2)
        Assert.AreEqual((byte)1, result)

    [<TestMethod>]
    member this.TestSubAtBoundary () =
        let result = IntMath.sub((byte)3, (byte)3)
        Assert.AreEqual((byte)0, result)

    [<TestMethod>]
    member this.TestSubOverBoundary () =
        let result = IntMath.sub((byte)3, (byte)4)
        Assert.AreEqual((byte)0, result)

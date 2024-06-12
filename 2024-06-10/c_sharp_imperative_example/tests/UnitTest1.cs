using imperative_example;

namespace tests;

[TestClass]
public class UnitTest1
{
    [TestMethod]
    public void Test_main()
    {
        var computerGroups = new List<ComputerGroup>(){
            new ComputerGroup(){
                Name = "TestGroup1",
                Computers = new List<Computer>(){
                    new Computer(){
                        Name = "TestComputer1",
                        IpAddresses = new List<string>(){
                            "1.2.3.4",
                            "2.3.4.5"
                        }
                    }
                }
            },
            new ComputerGroup(){
                Name = "TestGroup2",
                Computers = new List<Computer>(){
                    new Computer(){
                        Name = "TestComputer2",
                        IpAddresses = new List<string>(){
                            "1.2.3.4",
                            "2.3.4.5"
                        }
                    }
                }
            },
        };

        computerGroups.Validate();
    }
}
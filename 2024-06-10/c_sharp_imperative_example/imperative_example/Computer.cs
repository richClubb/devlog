namespace imperative_example;

public class Computer
{
    public string Name {get; set;} = string.Empty;
    public List<string> IpAddresses {get; set;} = new List<String>();

    public void Validate()
    {
        if (Name == string.Empty)
        {
            throw new Exception("Computer name can not be empty");
        }

        if (IpAddresses.Count() == 0)
        {
            throw new Exception($"Computer '{Name}' must have ip addresses");
        }

        if (IpAddresses.Count > 2)
        {
            throw new Exception($"Computer '{Name}' can not have more than 2 IpAddresses");
        }
    }
}
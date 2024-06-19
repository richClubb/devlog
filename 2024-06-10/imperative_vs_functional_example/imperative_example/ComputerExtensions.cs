using Common;

namespace imperative_example
{
    public static class ComputerExtensions
    {
        public static void Validate(this Computer computer)
        {
            if (computer.Name == string.Empty)
            {
                throw new Exception("Computer name cannot be empty");
            }

            if (computer.IpAddresses.Count == 0)
            {
                throw new Exception($"Computer '{computer.Name}' must have at least one IP address");
            }

            if (computer.IpAddresses.Count > 2)
            {
                throw new Exception($"Computer '{computer.Name}' cannot have more than two IP addresses");
            }
        }
    }
}

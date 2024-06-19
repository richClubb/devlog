namespace Common
{
    public class ComputerGroup
    {
        public string Name { get; set; } = string.Empty;
        public List<Computer> Computers { get; set; } = new List<Computer>();
    }
}

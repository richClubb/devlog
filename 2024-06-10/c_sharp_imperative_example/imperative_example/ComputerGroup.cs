namespace imperative_example;

public class ComputerGroup
{
    public string Name {get; set;} = string.Empty;
    public List<Computer> Computers {get; set;} = new List<Computer>();

    public void Validate()
    {
        if (Name == string.Empty)
        {
            throw new Exception("Computer group name can not be empty.");
        }

        if (Computers.Count() == 0)
        {
            throw new Exception($"Computer group '{Name}' must have computers.");
        }

        if (Computers.Count() > 2)
        {
            throw new Exception($"Computer group '{Name}' can not have more than 2 computers.");
        }

        Computers.ForEach(computer => 
            {
                try
                {
                    
                }
                catch (System.Exception)
                {
                    
                    throw;
                }
            }
        );
    }
}

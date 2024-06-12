namespace imperative_example;

public static class ComputerGroupExtensions
{
    public static void Validate(this List<ComputerGroup> computerGroups)
    {
        if (computerGroups.Count() == 0)
        {
            throw new Exception("Must be more than 0 computer groups");
        }

        if (computerGroups.Count() > 2)
        {
            throw new Exception("Must be no more than 2 computer groups");
        }

        var allIpAddresses = new List<string>();
        var allComputerGroupNames = new List<string>();
        var allComputerNames = new List<string>();

        foreach(var computerGroup in computerGroups)
        {
            allComputerGroupNames.Add(computerGroup.Name);

            computerGroup.Computers.Validate();
        }
    }
}

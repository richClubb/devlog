using Common;

namespace imperative_example
{
    public static class ComputerGroupExtensions
    {
        public static void Validate(this ComputerGroup computerGroup)
        {
            if (computerGroup.Name == string.Empty)
            {
                throw new Exception("Computer group name cannot be empty");
            }

            if (computerGroup.Computers.Count == 0)
            {
                throw new Exception("Computer group must have at least one computer");
            }

            if (computerGroup.Computers.Count > 2)
            {
                throw new Exception("Computer group cannot have more than two computers");
            }

            var computerNames = new HashSet<string>();
            var duplicateComputerNames = new HashSet<string>();

            foreach (var computer in computerGroup.Computers)
            {
                try
                {
                    computer.Validate();
                }
                catch (Exception ex)
                {
                    throw new Exception($"Error validating computer: {ex.Message}");
                }

                if (!computerNames.Add(computer.Name))
                {
                    duplicateComputerNames.Add(computer.Name);
                }
            }

            if (duplicateComputerNames.Count > 0)
            {
                throw new Exception($"Errror validating computer group '{computerGroup.Name}'. Duplicate computer names: {string.Join(", ", duplicateComputerNames)}");
            }
        }

        /// <summary>
        /// 
        /// validation:
        /// * must be more than 0, and fewer than 2 computer groups
        /// * computer groups names must be unique
        /// * computer names must be unique in the group
        /// * ip addresses must be unique across groups
        /// </summary>
        /// <param name="computerGroups"></param>
        /// <exception cref="Exception"></exception>
        public static void Validate(this List<ComputerGroup> computerGroups)
        {
            if (computerGroups.Count == 0)
            {
                throw new Exception("Computer groups must have at least one computer group");
            }

            if (computerGroups.Count > 2)
            {
                throw new Exception("Computer groups cannot have more than two computer groups");
            }

            var computerGroupNames = new HashSet<string>();
            var duplicateComputerGroupNames = new HashSet<string>();

            var ipAddresses = new HashSet<string>();
            var duplicateIpAddresses = new HashSet<string>();
            foreach (var computerGroup in computerGroups)
            {
                computerGroup.Validate();

                if (!computerGroupNames.Add(computerGroup.Name))
                {
                    duplicateComputerGroupNames.Add(computerGroup.Name);
                }

                foreach (var computer in computerGroup.Computers)
                {
                    try
                    {
                        computer.Validate();
                    }
                    catch (Exception ex)
                    {
                        throw new Exception($"Error validating computer: {ex.Message}");
                    }

                    if (!ipAddresses.Add(computer.Name))
                    {
                        duplicateIpAddresses.Add(computer.Name);
                    }
                }
            }

            if (duplicateComputerGroupNames.Count > 0)
            {
                throw new Exception($"Duplicate computer group names: {string.Join(", ", duplicateComputerGroupNames)}");
            }

            if (duplicateIpAddresses.Count > 0)
            {
                throw new Exception($"Duplicate ipAddressess found: {string.Join(", ", duplicateIpAddresses)}");
            }
        }
    }
}

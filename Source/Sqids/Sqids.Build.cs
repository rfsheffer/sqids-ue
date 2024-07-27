
using UnrealBuildTool;
using System.IO;

public class Sqids : ModuleRules
{
    private string SqidsPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/sqids-cpp/include")); }
    }

    public Sqids(ReadOnlyTargetRules Target) : base(Target)
    {
	    OptimizeCode = CodeOptimization.Never;
	    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(
            new string[]
            {
                "Sqids/Private",
                SqidsPath,
            }
        );
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
            }
        );
    }
}

// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class ProjectBM : ModuleRules
{
	public ProjectBM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
		, "UMG", "Slate", "SlateCore", "HeadMountedDisplay", "Niagara", "Sockets", "Networking"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		// Add the path to the include directory for your library
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../../Trd/FlatBuffer/flatbuffers-23.5.26/include/flatbuffers"));

		// Add the library
		if (Target.Configuration == UnrealTargetConfiguration.Debug)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../../Trd/FlatBuffer/flatbuffers-23.5.26/include/flatbuffers/Debug/flatbuffers.lib"));
		}
		else
		{
			//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../../Trd/FlatBuffer/flatbuffers-23.5.26/include/flatbuffers/Release/flatbuffers.lib"));
		}
	}
}

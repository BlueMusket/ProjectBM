// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;
using System.IO;

public class ProjectBM : ModuleRules
{
	public ProjectBM(ReadOnlyTargetRules Target) : base(Target)
	{
		// 엔진이 소스 코드를 찾거나 컴파일하지 않도록 지시
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
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../../Shared"));
		//PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/Shared/include"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/Shared/lib/x64/Shared.lib"));
        // Add the library
        if (Target.Configuration == UnrealTargetConfiguration.Debug)
		{
		}
		else
		{

		}
	}
}

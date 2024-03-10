// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectCY : ModuleRules
{
	public ProjectCY(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add("ProjectCY");
        PrivateIncludePaths.Add("ProjectCY/Widget");
        PrivateIncludePaths.Add("ProjectCY/Utility");
        PrivateIncludePaths.Add("ProjectCY/Utility/Manager");
        PrivateIncludePaths.Add("ProjectCY/Utility/StateMachine");
        PrivateIncludePaths.Add("ProjectCY/Utility/Scene");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

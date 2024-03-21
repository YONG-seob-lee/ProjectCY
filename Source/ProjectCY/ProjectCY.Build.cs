// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectCY : ModuleRules
{
	public ProjectCY(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add("ProjectCY");
        PrivateIncludePaths.Add("ProjectCY/Widget");
        PrivateIncludePaths.Add("ProjectCY/Widget/BuiltInWidget");
        PrivateIncludePaths.Add("ProjectCY/Utility");
        PrivateIncludePaths.Add("ProjectCY/Utility/Manager");
        PrivateIncludePaths.Add("ProjectCY/Utility/StateMachine");
        PrivateIncludePaths.Add("ProjectCY/Scene");
        PrivateIncludePaths.Add("ProjectCY/Table");
        PrivateIncludePaths.Add("ProjectCY/Table/Mapper");
        PrivateIncludePaths.Add("ProjectCY/Actor");
        PrivateIncludePaths.Add("ProjectCY/Actor/TelePort");
        PrivateIncludePaths.Add("ProjectCY/Unit");

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", "CoreUObject", "Engine", "InputCore", "Sequencer", "MessageLog", "AIModule", "Slate", "CommonUI"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { "EditorStyle" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

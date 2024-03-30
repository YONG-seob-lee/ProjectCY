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
        PrivateIncludePaths.Add("ProjectCY/Widget/MainHud");
        PrivateIncludePaths.Add("ProjectCY/Widget/Title");
        PrivateIncludePaths.Add("ProjectCY/Utility");
        PrivateIncludePaths.Add("ProjectCY/Utility/Manager");
        PrivateIncludePaths.Add("ProjectCY/Utility/StateMachine");
        PrivateIncludePaths.Add("ProjectCY/Scene");
        PrivateIncludePaths.Add("ProjectCY/Table");
        PrivateIncludePaths.Add("ProjectCY/Table/Mapper");
        PrivateIncludePaths.Add("ProjectCY/Actor");
        PrivateIncludePaths.Add("ProjectCY/Actor/AnimInstance");
        PrivateIncludePaths.Add("ProjectCY/Actor/Camera");
        PrivateIncludePaths.Add("ProjectCY/Actor/Components");
        PrivateIncludePaths.Add("ProjectCY/Actor/TelePort");
        PrivateIncludePaths.Add("ProjectCY/Unit");
        PrivateIncludePaths.Add("ProjectCY/Generic");

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", "CoreUObject", "Engine", "InputCore", "Sequencer",
	        "MessageLog", "AIModule", "Slate", "SlateCore", "UMG", "CommonUI",
        });

		PrivateDependencyModuleNames.AddRange(new string[] { "EditorStyle", "Niagara", "NiagaraUIRenderer", "CommonUI"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

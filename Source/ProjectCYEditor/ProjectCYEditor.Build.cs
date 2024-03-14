// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
//using Tools.DotNETCommon;

public class ProjectCYEditor : ModuleRules
{
	public ProjectCYEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "Sequencer", "PropertyEditor", "EditorScriptingUtilities", "Projects",
			"UnrealEd", "InputCore", "UMG"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate", "SlateCore", "EditorStyle", "DesktopPlatform", "AssetTools", "AssetRegistry", "LevelSequence"
		});

		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
    
		//string ProjectPath = Path.GetDirectoryName(Target.ProjectFile.ToString());	
	}
}
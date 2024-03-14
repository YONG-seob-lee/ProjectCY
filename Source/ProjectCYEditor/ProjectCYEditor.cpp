// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCYEditor.h"

#include "LevelEditor.h"
#include "EditorMenu/CY_SampleTool.h"
#include "Sequencer/Public/ISequencerModule.h"

#define LOCTEXT_NAMESPACE "CY_Editor"

IMPLEMENT_PRIMARY_GAME_MODULE(ICY_ProjectEditorModule, ProjectCYEditor, "ProjectCYEditor");

TSharedRef<FWorkspaceItem> ICY_ProjectEditorModule::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

class FCY_EditorCommands : public TCommands<FCY_EditorCommands>
{
public:
	FCY_EditorCommands() : TCommands(TEXT("CY Editor"), FText::FromString("Custom CY Editor Module"), NAME_None, FAppStyle::GetAppStyleSetName())
	{}
	
	virtual void RegisterCommands() override
	{
		UI_COMMAND(CommandInfo, "111111", "asdfasdfasdf222", EUserInterfaceActionType::Button, FInputChord());
	}

public:
	TSharedPtr<FUICommandInfo> CommandInfo;
};


void ICY_ProjectEditorModule::StartupModule()
{
	if (IsRunningCommandlet() == false)
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		const TSharedPtr<FExtensibilityManager> ExtensibilityManager =LevelEditorModule.GetMenuExtensibilityManager();
		if(ExtensibilityManager.IsValid() == false)
		{
			return;
		}

		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(TEXT("Window"), EExtensionHook::After, nullptr,
											FMenuBarExtensionDelegate::CreateRaw(this, &ICY_ProjectEditorModule::MakePulldownMenu));
		ExtensibilityManager->AddExtender(MenuExtender);

		//FDelegateHandle CustomHandle = EngineSequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FCY_MaterialTrackEditor::CreateTrackEditor));
	}

	ICY_ModuleInterface::StartupModule();
}

void ICY_ProjectEditorModule::ShutdownModule()
{
	for (const auto& TrackEditorHandle : TrackEditorHandleArr)
	{
		EngineSequencerModule.UnRegisterTrackEditor(TrackEditorHandle.Value);
	}
	
	TrackEditorHandleArr.Empty();
}

void ICY_ProjectEditorModule::AddModuleListener()
{
	ModuleListener.Add(MakeShareable(new ICY_SampleTool));
}

void ICY_ProjectEditorModule::AddMenuExtension(const FMenuExtensionDelegate& Delegate, FName ExtensionHook,
	const TSharedPtr<FUICommandList>& CommandList, EExtensionHook::Position Position)
{
	MenuExtender->AddMenuExtension(ExtensionHook, Position, CommandList, Delegate);
}

void ICY_ProjectEditorModule::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString(TEXT("CY Studio")),
		FText::FromString(TEXT("CY Stuido Editor")),
		FNewMenuDelegate::CreateRaw(this, &ICY_ProjectEditorModule::FillPulldownMenu),
		TEXT("CY Studio"),
		TEXT("CY Studio")
	);
}

void ICY_ProjectEditorModule::FillPulldownMenu(FMenuBuilder& menuBuilder)
{
	menuBuilder.BeginSection(TEXT(""), FText::FromName(EditorMenuNames::Dev));
	menuBuilder.AddMenuSeparator(EditorMenuNames::Dev);
	menuBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE


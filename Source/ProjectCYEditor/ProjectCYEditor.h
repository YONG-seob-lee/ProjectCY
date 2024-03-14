#pragma once

#include "CoreMinimal.h"

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_ModuleInterface.h"

//	다섯가지 종류의 TrackEditor 이 있다
//	1. AudioTrackEditor.h
//	2. CameraAnimTrackEditorHelper.h
//	3. MaterialTrackEditor.h
//	4. SpawnTrackEditor.h
//	5. SubTrackEditor.h
//	6. SubTrackEditorBase.h

enum ECY_TrackEditorType
{
	None = 0,
	MaterialTrackEditor,
};

namespace EditorMenuNames
{
	static const FName Dev = FName(TEXT("dev"));
}

/**
 * 
 */
class ICY_ProjectEditorModule : public ICY_ModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListener() override;
	
	void AddMenuExtension(const FMenuExtensionDelegate& Delegate, FName ExtensionHook
						, const TSharedPtr<FUICommandList>& CommandList = nullptr, EExtensionHook::Position Position = EExtensionHook::Before);

	static ICY_ProjectEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ICY_ProjectEditorModule>("ProjectCYEditor");
	}

	TSharedRef<FWorkspaceItem> GetMenuRoot() const { return MenuRoot; }
protected:
	static TSharedRef<FWorkspaceItem> MenuRoot;
	
private:
	void MakePulldownMenu(FMenuBarBuilder& menuBuilder);
	void FillPulldownMenu(FMenuBuilder& menuBuilder);
	
	TSharedPtr<class FExtender> MenuExtender;
	TMap<ECY_TrackEditorType, FDelegateHandle> TrackEditorHandleArr;

#define EngineSequencerModule ((FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer")))
};
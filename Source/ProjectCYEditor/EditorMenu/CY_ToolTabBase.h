#pragma once
#include "CY_ModuleInterface.h"
#include "ProjectCYEditor.h"

class ICY_ToolTabBase : public ICY_ModuleListenerInterface, public TSharedFromThis<ICY_ToolTabBase>
{
public:
	virtual ~ICY_ToolTabBase() override {}

	virtual void OnStartupModule() override
	{
		Initialize();
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateRaw(this, &ICY_ToolTabBase::SpawnTab))
			.SetGroup(ICY_ProjectEditorModule::Get().GetMenuRoot())
			.SetDisplayName(TabDisplayName)
			.SetTooltipText(ToolTipText)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), IconName));
	}

	virtual void OnShutdownModule() override
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabName);
	};
	
	virtual void Initialize()
	{
	};

	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& _TabSpawnArgs)
	{
		return SNew(SDockTab);
	};

	virtual void MakeMenuEntry(FMenuBuilder& _MenuBuilder)
	{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(_MenuBuilder, TabName);
	};


protected:
	FName TabName;
	FText TabDisplayName;
	FText ToolTipText;
	FName IconName;
};

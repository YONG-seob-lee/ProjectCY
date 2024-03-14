#pragma once
#include "CY_ToolTabBase.h"

class ICY_SampleTool : public ICY_ToolTabBase
{
public:
	virtual ~ICY_SampleTool() override {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	virtual void Initialize() override;

	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& _TabSpawnArgs) override;
};

class ICY_SampleToolPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ICY_SampleToolPanel)
	{
		
	}
	SLATE_ARGUMENT(TWeakPtr<class ICY_SampleTool>, SampleTool);
	
	SLATE_END_ARGS();

	void Construct(const FArguments& Arg);

protected:
	TWeakPtr<ICY_SampleTool> SampleTool;
};
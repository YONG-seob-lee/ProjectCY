#include "CY_SampleTool.h"

#include "Widgets/Layout/SScrollBox.h"

void ICY_SampleTool::OnStartupModule()
{
	Initialize();
	ICY_ToolTabBase::OnStartupModule();
	ICY_ProjectEditorModule::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &ICY_SampleTool::MakeMenuEntry),
													EditorMenuNames::Dev);
}

void ICY_SampleTool::OnShutdownModule()
{
	ICY_ToolTabBase::OnShutdownModule();
}

void ICY_SampleTool::Initialize()
{
	TabName = "Sample tool";
	TabDisplayName = FText::FromString("Sample Tool");
	ToolTipText = FText::FromString("Sample ToolTipText");
}

TSharedRef<SDockTab> ICY_SampleTool::SpawnTab(const FSpawnTabArgs& _TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).TabRole(NomadTab)[SNew(ICY_SampleToolPanel).SampleTool(SharedThis(this))];
	return SpawnedTab;
}

void ICY_SampleToolPanel::Construct(const FArguments& Arg)
{
	SampleTool = Arg._SampleTool;

	ChildSlot
	[
		SNew(SScrollBox) + SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor::Emerald)
			.Padding(10.f)
			[
				SNew(STextBlock).Text(FText::FromString(TEXT("This is Sample Tab.")))
			]
		]
	];
}

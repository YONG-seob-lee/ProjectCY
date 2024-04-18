// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_Title.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Title : public UCY_Widget
{
	GENERATED_BODY()
	
public:
	static FName GetWidgetName() { return TEXT("Title"); }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

private:
	void OnClickStartButton();
	void OnClickExitButton();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_TitleButton> CPP_StartButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_TitleButton> CPP_ExitButton = nullptr;
};

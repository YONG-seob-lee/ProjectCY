// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_Logo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Logo : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Logo"); }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	void OnClickBlankButton();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCY_Button> CPP_BlankButton = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_Toast.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Toast : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath("/Game/Widget/BuiltInWidget/ToastWidget.ToastWidget"); }

	void ShowToast(const FString& Message);

protected:
	virtual void OnAnimFinished(const FName& AnimName) override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MessageText;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_MainHud.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_MainHud : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("MainHud"); }
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHud> CPP_TopHudWidget = nullptr;
};

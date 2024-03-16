// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CY_BuiltInWidgetTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_BuiltInWidgetTool : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE TObjectPtr<class UCY_Widget_DialogScreenFader> GetDialogScreenFader() const { return DialogScreenFader;}
	FORCEINLINE TObjectPtr<class UCY_Widget_Loading> GetLoadingWidget() const { return LoadingWidget; };

private:
	UPROPERTY()
	TObjectPtr<UCY_Widget_DialogScreenFader> DialogScreenFader = nullptr;

	UPROPERTY()
	TObjectPtr<UCY_Widget_Loading> LoadingWidget = nullptr;
};

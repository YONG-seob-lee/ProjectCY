// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "GenericWidget/CY_WidgetSwitcher.h"
#include "CY_Widget_WorldMapIcon.generated.h"

enum ECY_IconSelectState
{
	UnSelect = 0,
	Select = 1,
};
/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_WorldMapIcon : public UCY_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE static FName GetWidgetName() { return TEXT("WorldMapIcon"); }
	FORCEINLINE void SetSwitchIcon(ECY_IconSelectState SelectState) const { CPP_WidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(SelectState)); } 
	FORCEINLINE void SetTargetVector(const FVector& _TargetVector) { TargetVector = _TargetVector; }
	FORCEINLINE void SetOnClickAcceptMoveFunction(const TFunction<void(FVector TargetVector)>& Function)  { OnClickAcceptMoveCallback = Function; }
	
	void InitializeIcon();
	void SetIconTexture(TObjectPtr<UTexture2D> Texture) const;

	void SetOnPressIcon();
	void SetOnReleaseIcon();
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_WidgetSwitcher> CPP_WidgetSwitcher = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_IconImage = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Button> CPP_Button = nullptr;

	FVector TargetVector = FVector::ZeroVector;

	TFunction<void(FVector TargetVector)> OnClickAcceptMoveCallback = nullptr;
};

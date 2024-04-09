// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_WorldMapIcon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_WorldMapIcon : public UCY_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE static FName GetWidgetName() { return TEXT("WorldMapIcon"); }
	
	void InitStaticPosition(TObjectPtr<UTexture2D> IconTexture, const FVector& _StaticPosition) const;
	void SetIconTexture(TObjectPtr<UTexture2D> Texture) const;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_IconImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Button> CPP_Button = nullptr;
};

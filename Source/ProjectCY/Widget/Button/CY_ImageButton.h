// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_ImageButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_ImageButton : public UCY_Widget
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	
	void SetOnClickImageButton(const UCommonButtonBase::FCommonButtonEvent& Event) const;
	
private:
	UPROPERTY(Category = UCY_ImageButton, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Texture2D = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Button> CPP_Button = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Image = nullptr;
};

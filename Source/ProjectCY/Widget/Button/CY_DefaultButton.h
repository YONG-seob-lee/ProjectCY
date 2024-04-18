// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_DefaultButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_DefaultButton : public UCY_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetData(const FLinearColor& BGColor, const FString& _ButtonText) const;
	void SetOnClickButton(const UCommonButtonBase::FCommonButtonEvent& CommonButtonEvent) const;

private:
	UPROPERTY(Category= UCY_DefaultButton, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FLinearColor Color = FLinearColor::White;
	UPROPERTY(Category= UCY_DefaultButton, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString ButtonText = "Blank Text";

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Button> CPP_DefaultButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_BGImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ButtonText = nullptr;
};

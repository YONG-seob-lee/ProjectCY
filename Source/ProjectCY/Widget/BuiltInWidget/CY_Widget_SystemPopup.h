// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_SystemPopup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_SystemPopup : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("SystemPopup"); }

	void ShowSystemPopup(const FCY_SystemPopupParameter& SystemPopupParam);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PopupTitleText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_ImageButton> CPP_ExitButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ContentsText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_DefaultButtonBase> CPP_ConfirmButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_DefaultButtonBase> CPP_CancelButton = nullptr;
};

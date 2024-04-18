// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CY_Widget.h"
#include "CY_TitleButton.generated.h"

/**
 *
 */
UCLASS()
class PROJECTCY_API UCY_TitleButton : public UCY_Widget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

	void SetOnClickEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const;
	void UnbindClickEvent()const ;
	void SetButtonText(const FString& ButtonText) const;
	
	void SetText(const FString& ButtonString) const;
	
	void SetOnClickedDelegate(const UCommonButtonBase::FCommonButtonEvent& Event) const;

protected:
	void SetStyleChange(TSubclassOf<UCommonTextStyle> _TextStyle) const;
	
private:
	void OnClicked();

	UPROPERTY(Category = UCY_Button, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonTextStyle> TextStyle;
	UPROPERTY(Category = UCY_Button, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseButtonText = true;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCY_Button> CPP_ButtonBase = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonTextBlock> CPP_CommonText = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_Text_Panel = nullptr;
};
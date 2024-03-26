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

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;

	void SetButtonText(const FString& ButtonText) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCY_Button> CPP_ButtonBase = nullptr;
};
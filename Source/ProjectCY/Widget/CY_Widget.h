// Fill out your copyright notice in the Description page of Project Settings.asd

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CY_Define.h"
#include "CY_Widget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class PROJECTCY_API UCY_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void MakeButtonPool();

	UPROPERTY()
	TArray<class UCY_Button*> Buttons;
};
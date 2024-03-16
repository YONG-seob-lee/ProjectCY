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

	void PlayAnimationByName(FName Name, float StartTime = 0.f, int32 LoopCount = 1, EUMGSequencePlayMode::Type PlayType = EUMGSequencePlayMode::Forward, float Speed = 1.f);
	UPROPERTY()
	TArray<class UCY_Button*> Buttons;
};
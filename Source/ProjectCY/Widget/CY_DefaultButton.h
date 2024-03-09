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
};
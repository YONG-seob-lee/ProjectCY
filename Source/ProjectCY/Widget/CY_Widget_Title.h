// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_Title.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Title : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Title"); }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
//#include "CY_SceneDefine.generated.h"

/**
 * 
 */

enum class ECY_FadeType
{
	None = 0,
	FadeIn,
	FadeOut,
};

enum class ECY_FadeStatus
{
	None = 0,
	FadeInAnimation,
	FadeOutAnimation,
};

enum class ECY_FadeStep
{
    Ready = 0,
	EnterFadeIn,
	ExitFadeIn,
	EnterFadeOut,
	ExitFadeOut,
};

enum class ECY_FadeStyle
{
	None = 0,
	Dialog,
	
};

enum class ECY_LoadingPageType
{
	None = 0,
	EnterFirst,
};


// UCLASS()
// class PROJECTCY_API UCY_SceneDefine : public UObject
// {
// 	GENERATED_BODY()
// };

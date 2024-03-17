﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CY_SceneDefine.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECY_GameSceneType : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	
	Title		UMETA(DisplayName = "Title"),
};

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

enum class ECY_ChangeSceneStep
{
	Ready,
	LoadLevel,
	PrepareSceneState,
	Complete,
};

USTRUCT()
struct FCY_ChangeSceneData
{
	GENERATED_USTRUCT_BODY()

	ECY_GameSceneType SceneType;
	ECY_ChangeSceneStep Step;
	FName LevelPackagePath;
};

DECLARE_DELEGATE_OneParam(FCY_LoadLevelInitialized, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FCY_ChangeSceneDelegate, ECY_GameSceneType);
DECLARE_MULTICAST_DELEGATE_OneParam(FCY_LoadLevelDelegate, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FCY_ChangeSceneState, uint8);
// UCLASS()
// class PROJECTCY_API UCY_SceneDefine : public UObject
// {
// 	GENERATED_BODY()
// };
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Core/Public/Logging/LogMacros.h"
//#include "CY_Define.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ProjectCyLog, Log, All);

#define CY_LOG(InFormat, ...) UE_LOG(ProjectCyLog, Log, InFormat, ##__VA_ARGS__)

#define CY_CHECK(expr) check(expr)

#define CY_NewObject NewObject
#define CY_DeleteObject(Object) {										\
									CY_CHECK(Object != nullptr);					\
									Object->ConditionalBeginDestroy();	\
								};

DECLARE_DELEGATE_OneParam(FButtonEventDelegate, class UCY_Button*);

UENUM(BlueprintType)
enum class ECY_LaunchProcessType : uint8
{
	None = 0,

	CreateManager,
	RegistTick,
	RegistState,
	LoadBaseWorld,
	
	ProcessFinished
};

UENUM(BlueprintType)
enum class ECY_GameSceneType : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	
	Title		UMETA(DisplayName = "Title"),
};

/**
 *
 */
//UCLASS()
//class PROJECTCY_API UCY_Define : public UObject
//{
//	GENERATED_BODY()
//
//};
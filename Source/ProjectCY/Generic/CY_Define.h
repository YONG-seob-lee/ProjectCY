// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

typedef int32 CY_Handle;
constexpr int32 InvalidUnitHandle = 0;

DECLARE_DELEGATE_OneParam(FButtonEventDelegate, class UCY_Button*);

UENUM(BlueprintType)
enum class ECY_LaunchProcessType : uint8
{
	None = 0,

	BasicUtility,
	CreateManager,
	RegistManager,
	RegistTick,
	LoadBaseWorld,
	ProcessFinished,

	End
};

UENUM(BlueprintType)
enum class ECY_Axis_Type : uint8
{
	Left	UMETA(DisplayName = "Axis_Type_Left"),
	Right	UMETA(DisplayName = "Axis_Type_Left"),
	Pinch	UMETA(DisplayName = "Axis_Type_Left"),
};

UENUM(BlueprintType)
enum class ECY_Action_Type : uint8
{
	ActionUpDown	UMETA(DisplayName = "Action_Type_UpDown"),
	ActionLeftRight	UMETA(DisplayName = "Action_Type_LeftRight"),
};

UENUM(BlueprintType)
enum class ECY_Touch_Event : uint8
{
	Down	UMETA(DisplayName = "Touch_Event_Down"),
	Up		UMETA(DisplayName = "Touch_Event_Up"),
	Move	UMETA(DisplayName = "Touch_Event_Move"),
};

UENUM(BlueprintType)
enum class ECY_AndroidButton_Type : uint8
{
	Back	UMETA(DisplayName = "AndroidButton_Back"),
	Menu	UMETA(DisplayName = "AndroidButton_Menu"),
};

DECLARE_DELEGATE_TwoParams(FBindAllKeysDelegate, const FKey&, bool);
﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "UObject/Object.h"
#include "CY_WidgetDefine.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FCY_CreateWidget, const FName&);
DECLARE_MULTICAST_DELEGATE_OneParam(FCY_DestroyWidget, const FName&);

namespace DefaultWidgetAnimation
{
	const FName Appearance = TEXT("Appearance");
	const FName DisAppearance = TEXT("DisAppearance");
	
	const FName AppearanceDirect = TEXT("AppearanceDirect");
	const FName DisAppearanceDirect = TEXT("DisAppearanceDirect");
	
	const FName Idle = TEXT("Idle");
}

UENUM(BlueprintType)
enum class ECY_ExclusiveGroup : uint8
{
	InVaild = 0,
	ContentMenu = 1,
	ContentSubMenu1 = 2,
	ContentSubMenu2 = 3,
	ContentSubMenu3 = 4,
	ContentSubMenu4 = 5,
	ContentSubMenu5 = 6,
	ContentSubMenu6 = 7,
	ContentSubMenu7 = 8,
	ContentSubMenu8 = 9,
	ContentSubMenu9 = 10,
	ContentSubMenu10 = 11,
	ContentSubMenu11 = 12,
	ContentSubMenu12 = 13,
	ContentSubMenu13 = 14,
	ContentSubMenu14 = 15,
	ContentSubMenu15 = 16,
	ContentSubMenu16 = 17,
	ContentSubMenu17 = 18,
	ContentSubMenu18 = 19,
	ContentSubMenu19 = 20,
	ContentSubMenu20 = 21,
	ContentSubMenu21 = 22,
	ContentSubMenu22 = 23,
	ContentSubMenu23 = 24,
	ContentSubMenu24 = 25,
	ContentSubMenu25 = 26,
	ContentSubMenu26 = 27,
	TopMenu = 28,
	Max
};

struct FCY_ResourceWidgetInfo
{
	FCY_ResourceWidgetInfo(): zOrder(0), ExclusiveGroup(), NotRender3D(false), bNotClosing(false), CreateTime(0) {}

	FString File;
	FName TypeName;
	int32 zOrder;
	ECY_ExclusiveGroup ExclusiveGroup;
	bool NotRender3D;
	bool bNotClosing;
	float CreateTime;
	
	FORCEINLINE const FName& GetWidgetName() const { return TypeName; }
	FORCEINLINE const ECY_ExclusiveGroup& GetExclusiveGroup() const { return ExclusiveGroup; }
};

UENUM()
enum class ECY_SelectButtonState
{
	None = 0,
	Ok,
	Cancel,
	OkCancel,
};

struct FCY_SystemPopupParameter
{
	FCY_SystemPopupParameter() {}

	FString TitleText = FString();
	bool bShowExitButton = false;
	FString ContentsText = FString();
	ECY_SelectButtonState SelectButtonState = ECY_SelectButtonState::OkCancel;

	UCommonButtonBase::FCommonButtonEvent OnClickExitEvent;
	UCommonButtonBase::FCommonButtonEvent OnClickConfirmEvent;
	UCommonButtonBase::FCommonButtonEvent OnClickCancelEvent;
};
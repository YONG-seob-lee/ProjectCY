// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_CameraDefine.generated.h"

/**
 * 
 */

namespace CameraSubType
{
	const FString Main = TEXT("Main");
	const FString Back = TEXT("Back"); 
	const FString Drone_01 = TEXT("Drone_01");
	const FString Drone_02 = TEXT("Drone_02");
	const FString Drone_03 = TEXT("Drone_03");
}

USTRUCT()
struct FCY_CameraData
{
    GENERATED_USTRUCT_BODY()

	FCY_CameraData() {}
	FCY_CameraData(float _FieldOfView, float _Distance, const FRotator& _Rotate, const FVector& _TargetOffset)
		: FieldOfView(_FieldOfView), Distance(_Distance), Rotate(_Rotate), TargetOffset(_TargetOffset) {}

	float FieldOfView = 0.f;
	float Distance = 0.f;
	FRotator Rotate = FRotator::ZeroRotator;
	FVector TargetOffset = FVector::ZeroVector;
};
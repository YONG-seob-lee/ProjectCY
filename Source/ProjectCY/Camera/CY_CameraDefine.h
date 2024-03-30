// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_CameraDefine.generated.h"

/**
 * 
 */

USTRUCT()
struct FCY_CameraData
{
    GENERATED_USTRUCT_BODY()

	FCY_CameraData() {}
	FCY_CameraData(float _FieldOfView, float _Distance, const FRotator& _Rotate, const FVector& _TargetOffset)
		: FieldOfView(_FieldOfView), Distance(_Distance), Rotate(_Rotate), TargetOffset(_TargetOffset)
    {
    	ComputeRotateVector = Rotate.RotateVector(FVector(0.f, 1.f, 0.f) * Distance);
    }
	
	float FieldOfView = 0.f;
	float Distance = 0.f;
	FRotator Rotate = FRotator::ZeroRotator;
	FVector TargetOffset = FVector::ZeroVector;
	FVector ComputeRotateVector = FVector::ZeroVector; 
};
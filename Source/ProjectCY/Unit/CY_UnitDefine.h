// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CY_UnitDefine.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCY_CharacterLodValues
{
    GENERATED_BODY()
	FCY_CharacterLodValues() {}

public:
	UPROPERTY(Category = "FCY_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CullDistance = 0;

	UPROPERTY(Category = "FCY_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 OutLineCullDistance = 0;

	// not used
	UPROPERTY(Category = "FCY_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) 
	int32 AnimMaxDistanceFactor = 0;

	UPROPERTY(Category = "FCY_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<float> AnimThresholdTable;

	UPROPERTY(Category = "FCY_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 BaseNonRenderedUpdateRate = 0;

	float CullDistanceScale = 1.0f;
	float OutLineCullDistanceScale = 1.0f;
	bool  bVisibleOutLine = true;
};

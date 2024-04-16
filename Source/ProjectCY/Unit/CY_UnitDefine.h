// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitDefine.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FCY_UnitActorTickDelegate, TObjectPtr<class UCY_UnitBase>);

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

UENUM()
enum ECY_UnitState
{
	None = 0,
	PalWorld_Field,
};

UENUM(BlueprintType)
enum class ECY_UnitActionState : uint8
{
	None = 0			UMETA(DisplayName = "None"),
	Player_Normal				UMETA(DisplayName = "Player_Normal"),
};

UENUM()
enum class ECY_InteractionType : uint8
{
	None = 0			UMETA(DisplayName = "None"),
	Teleport_Map		UMETA(DisplayName = "Teleport_Map"),
};

namespace NpcRoleType
{
	const FString Interaction = TEXT("Interaction");
	const FString Bubble = TEXT("Bubble");
};
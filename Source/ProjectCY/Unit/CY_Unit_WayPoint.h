// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitBase.h"
#include "Character/CY_CharacterBase.h"
#include "CY_Unit_WayPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Unit_WayPoint : public UCY_UnitBase
{
	GENERATED_BODY()
public:
	FORCEINLINE TObjectPtr<ACY_CharacterBase> GetCharacterActor() const { return CharacterBase.Get(); }

private:
	TWeakObjectPtr<ACY_CharacterBase> CharacterBase = nullptr;
};

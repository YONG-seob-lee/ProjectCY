// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitBase.h"
#include "Character/CY_CharacterBase.h"
#include "CY_Unit_TeleportPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Unit_TeleportPoint : public UCY_UnitBase
{
	GENERATED_BODY()
public:
	
private:
	TWeakObjectPtr<ACY_CharacterBase> CharacterBase = nullptr;
};

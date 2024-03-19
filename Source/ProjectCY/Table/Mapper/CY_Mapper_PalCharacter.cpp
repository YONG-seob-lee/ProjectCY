// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Mapper_PalCharacter.h"
#include "CY_TableDefine.h"

void UCY_Mapper_PalCharacter::Initialize(TObjectPtr<UCY_TableManager> Mng)
{
	BuildTable(Mng, ECY_TableDataType::Pal_Character, PalCharacterMap);
}

void UCY_Mapper_PalCharacter::Finalize()
{
	PalCharacterMap.Empty();
}
 
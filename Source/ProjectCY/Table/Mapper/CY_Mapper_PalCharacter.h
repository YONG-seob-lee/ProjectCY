// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/CY_TableMapper.h"
#include "Engine/DataTable.h"
#include "CY_Mapper_PalCharacter.generated.h"

// todo 용섭 : 나중에 엑셀로 헤더를 만드는 작업이 요구됨
USTRUCT()
struct FPal_Character : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

};
/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Mapper_PalCharacter : public UCY_TableMapper
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(TObjectPtr<UCY_TableManager> Mng) override;
	virtual void Finalize() override;


private:
	TMap<int32, TObjectPtr<FPal_Character>> PalCharacterMap;
};

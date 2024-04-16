// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_NpcContents.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Mapper_NpcContents : public UCY_TableMapper
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UCY_TableManager> Mng) override;
	virtual void Finalize() override;

	void GetNpcContentDatas(int32 UnitId, TMap<FString, int32>& ContentDatas);

	TMap<int32, TObjectPtr<struct FNpc_Contents>> NpcContents;
};

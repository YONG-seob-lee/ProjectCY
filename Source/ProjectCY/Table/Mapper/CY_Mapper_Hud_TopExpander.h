// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_Hud_TopExpander.generated.h"

/**
 * 
 */

namespace ExpanderButtonType
{
	const FString Blank = TEXT("Blank");
	const FString Exit = TEXT("Exit");
}

UCLASS()
class PROJECTCY_API UCY_Mapper_Hud_TopExpander : public UCY_TableMapper
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UCY_TableManager> Mng) override;
	virtual void Finalize() override;

	FORCEINLINE void GetExpanderData(TMap<FString, TObjectPtr<struct FHud_TopExpander>>& _TopExpanderDatas) const { _TopExpanderDatas = TopExpanderDatas; }

private:
	TMap<FString, TObjectPtr<struct FHud_TopExpander>> TopExpanderDatas;
};

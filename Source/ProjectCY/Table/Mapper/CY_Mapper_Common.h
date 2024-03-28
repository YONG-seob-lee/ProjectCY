// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_Common.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Mapper_Common : public UCY_TableMapper
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UCY_TableManager> Mng) override;
	virtual void Finalize() override;

	int32 GetParam01(const FString& CommonContents);
	int32 GetParam02(const FString& CommonContents);
	float GetParam03(const FString& CommonContents);
	float GetParam04(const FString& CommonContents);
	
private:
	TMap<FString, TObjectPtr<FCommon>> CommonDatas;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_TableMapper.h"
#include "Resource_Widget.h"
#include "CY_Mapper_Resource_Widget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Mapper_Resource_Widget : public UCY_TableMapper
{
	GENERATED_BODY()
public:
	
	virtual void Initialize(TObjectPtr<UCY_TableManager> Mng) override;
	virtual void Finalize() override;
	
	TObjectPtr<FResource_Widget> GetResourceWidgetData(const FName& TypeName);
	
private:
	TMap<FName, TObjectPtr<FResource_Widget>> ResourceWidgetDatas;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneBase.h"
#include "CY_SceneLogo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_SceneLogo : public UCY_SceneBase
{
	GENERATED_BODY()

protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
};

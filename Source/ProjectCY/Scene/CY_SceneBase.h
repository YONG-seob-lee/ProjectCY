// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_StateBase.h"
#include "CY_SceneBase.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FCY_LoadingProcessDelegate, float);
/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_SceneBase : public UCY_StateBase
{
	GENERATED_BODY()

public:
	void TickLoading(float Delta);
	bool IsCompleteLoading();

protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

protected:
	virtual bool LoadingPreProcess(float DeltaTime);
	virtual bool LoadingProcess(float DeltaTime);
	virtual bool LoadingPostProcess(float DeltaTime);

private:
	TArray<FCY_LoadingProcessDelegate> LoadingProcessDelegates;
};

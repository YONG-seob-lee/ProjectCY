// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "CY_ContentsProcessManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_ContentsProcessManager : public UObject, public UCY_Singleton<UCY_ContentsProcessManager>
{
	GENERATED_BODY()
public:
	UCY_ContentsProcessManager();
	~UCY_ContentsProcessManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> StateMachine = nullptr;

#define gContentProcessMng (*UCY_ContentsProcessManager::GetInstance())
};

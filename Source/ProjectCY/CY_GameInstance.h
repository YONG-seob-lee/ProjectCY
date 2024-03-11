// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CY_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UCY_GameInstance();
	virtual ~UCY_GameInstance() override;

	virtual void Init() override;
	virtual void Shutdown();

	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	bool Tick(float DeltaSeconds);
private:
	void CreateGameCore();
	void CreateManagers();
	void DestroyManagers();
	void DestroyGameCore();

	void RegistState();

	void LoadBaseWorld();

	FDelegateHandle TickDelegateHandle;

	#define	gInstanceMng (TObjectPtr<UCY_GameInstance::GetInstance()>)
};

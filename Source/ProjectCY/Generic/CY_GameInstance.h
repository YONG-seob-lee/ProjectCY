// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chaos/AABB.h"
#include "Engine/GameInstance.h"
#include "CY_GameInstance.generated.h"

/**
 * 
 */
UCLASS(config = game)
class PROJECTCY_API UCY_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	UCY_GameInstance();
	virtual ~UCY_GameInstance() override;

	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	bool Tick(float DeltaSeconds);
	
	FORCEINLINE TObjectPtr<UCY_GameInstance> GetGameInstance() { return this; }
private:
	
	void ProcessInitialize(uint8& CurrentProcessType);

	bool CreateBasicUtility();
	bool CreateManagers();
	void DestroyManagers();
	void DestroyBasicUtility();

	void GameInstanceStart(UGameInstance* GameInstance);
	
	bool RegisterTick();
	bool RegisterState();

	bool LoadBaseWorld();

	void RestartGame();

	UPROPERTY(Category = UCY_GameInstance, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> BaseWorld;
	
	UPROPERTY(Category = UCY_GameInstance, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTree> SceneBTAsset = nullptr;
	FTSTicker::FDelegateHandle TickDelegateHandle;
};

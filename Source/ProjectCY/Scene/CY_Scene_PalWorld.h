// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
#include "CY_SceneBase.h"
#include "CY_Scene_PalWorld.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Scene_PalWorld : public UCY_SceneBase
{
	GENERATED_BODY()

public:
	UCY_Scene_PalWorld();
	virtual ~UCY_Scene_PalWorld() override;

protected:
	virtual void Begin() override;
	virtual void Exit() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool LoadingPostProcess(float DeltaTime) override;
private:
	void CreatePlayer();
	void ChangeCamera();
	void TransportPlayer() const;
	void DestroyPlayer();

	TWeakObjectPtr<class UCY_BasePlayer> Player;

	CY_Handle NewPlayerHandle = InvalidUnitHandle;
	
	UPROPERTY()
	FVector PlayerDefaultPosition = FVector::ZeroVector;

	UPROPERTY()
	FRotator PlayerDefaultRotator = FRotator::ZeroRotator;

	TWeakObjectPtr<class ACYPlayerSpawnPoint> PlayerSpawnPoint = nullptr;
	TMap<int32, FTransform> TeleportPoints;
};

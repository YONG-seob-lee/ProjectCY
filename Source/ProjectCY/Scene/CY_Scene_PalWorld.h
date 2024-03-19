// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	void CreatePlayer();
	void DestroyPlayer();

	TWeakObjectPtr<class UCY_BasePlayer> Player;
	TMap<int32, FTransform> TeleportPoints;
};

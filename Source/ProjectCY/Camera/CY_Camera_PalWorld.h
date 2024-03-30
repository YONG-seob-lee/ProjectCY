// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_CameraDefine.h"
#include "CY_StateBase.h"
#include "Components/CapsuleComponent.h"
#include "CY_Camera_PalWorld.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Camera_PalWorld : public UCY_StateBase
{
	GENERATED_BODY()
public:
	UCY_Camera_PalWorld();
	virtual ~UCY_Camera_PalWorld() override;
	
	virtual void Initialize(uint8 Index, const FName& Name) override;
	virtual void Finalize() override;
	
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

private:
	void ActorTickFunc(float DeltaTime, TObjectPtr<class UCY_UnitBase> Unit);
	
	void ComputeCameraData(const FVector& UnitVector) const;
	
	TMap<FString, TObjectPtr<class ACY_CameraActor>> Cameras;
	TObjectPtr<ACY_CameraActor> MainCamera = nullptr;
	FCY_CameraData CameraData;
	
	TWeakObjectPtr<UCapsuleComponent> CameraCapsuleComponent;

	FDelegateHandle ActorTickEvent;
};

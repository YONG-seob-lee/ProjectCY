// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "UObject/Object.h"
#include "CY_CameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_CameraManager : public UObject, public UCY_Singleton<UCY_CameraManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	void ResetData();

	void DestroyAllCameras();
	
	void ChangeCamera(uint8 Index, bool bInstant = true);

private:

	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> CameraState = nullptr;
	
	TMap<FName, int32> CameraNames;
	TMap<FString, CY_Handle> SceneCameras;
#define gCameraMng (*UCY_CameraManager::GetInstance())
};

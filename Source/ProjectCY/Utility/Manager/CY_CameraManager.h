// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
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
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float _DeltaTime) override;

	void RegisterCameras();
	
	void ResetData();

	void DestroyAllCameras();

	FORCEINLINE TTuple<FString, FString> GetCurrentActiveCameraType() { return CurrentActiveCamera; }
	TObjectPtr<class ACY_CameraActor> GetCameraActor(const FString& CameraType, const FString& CameraSubType);
	TObjectPtr<ACY_CameraActor> GetCameraActor(const TTuple<FString, FString>& CameraType);

	TObjectPtr<ACY_CameraActor> GetCurrentActiveCameraActor();

	// step1. Activate Camera State
	void ChangeCamera(uint8 Index, bool bInstant = true) const;

	// step2. Valid Check Has Camera Actor 
	bool HasCamera(ECY_GameCameraType CameraType) const;
	
	// step2. Create Camera Actor
	TMap<FString, TObjectPtr<class ACY_CameraActor>> CreateCameraActor(TSubclassOf<ACY_CameraActor> CameraActorType, ECY_GameCameraType _CameraType);
	
	// step3. Activate Camera Actor
	TObjectPtr<ACY_CameraActor> ActiveCamera(ECY_GameCameraType _CameraType, const FString& CameraSubType, float BlendTime = 0.f);
	
	TObjectPtr<class UCY_StateBase> GetCurrentState() const;
private:
	void RegistCameraState(uint8 Index, const FName& Name, TSubclassOf<UCY_StateBase> SceneType);

	void AddCameraActor(const FString& CameraType, const FString& CameraSubType, TObjectPtr<ACY_CameraActor> CameraActor);
	
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> CameraStateMachine = nullptr;
	
	TMap<FString, TMap<FString, TObjectPtr<ACY_CameraActor>>> CameraActors;

	TTuple<FString, FString> CurrentActiveCamera = {};
	
#define gCameraMng (*UCY_CameraManager::GetInstance())
};

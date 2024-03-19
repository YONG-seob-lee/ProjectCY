// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CameraManager.h"

#include "CY_StateMachine.h"

void UCY_CameraManager::Initialize()
{
	UCY_Singleton<UCY_CameraManager>::Initialize();
}

void UCY_CameraManager::Finalize()
{
	UCY_Singleton<UCY_CameraManager>::Finalize();
}

void UCY_CameraManager::Tick(float _DeltaTime)
{
	UCY_Singleton<UCY_CameraManager>::Tick(_DeltaTime);
}

void UCY_CameraManager::ResetData()
{
	CameraNames.Empty();
}

void UCY_CameraManager::DestroyAllCameras()
{
	SceneCameras.Empty();
}

void UCY_CameraManager::ChangeCamera(uint8 Index, bool bInstant /* = true */)
{
	if(CameraState)
	{
		CameraState->SetState(Index, bInstant);
	}
}

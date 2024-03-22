// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_InputManager.h"

#include "CY_BasicGameUtility.h"
#include "CY_GameInstance.h"
#include "CY_Pawn_Input.h"

void UCY_InputManager::Initialize()
{
	UCY_Singleton<UCY_InputManager>::Initialize();
}

void UCY_InputManager::Finalize()
{
	UCY_Singleton<UCY_InputManager>::Finalize();
}

void UCY_InputManager::Tick(float _DeltaTime)
{
	UCY_Singleton<UCY_InputManager>::Tick(_DeltaTime);
}

void UCY_InputManager::DestroyInputPawn()
{
	if(InputPawn != nullptr)
	{
		InputPawn->Destroy();

		if(InputPawn->IsRooted())
		{
			InputPawn->RemoveFromRoot();
		}

		UCY_BasicGameUtility::GetGameWorld()->DestroyActor(InputPawn);
		
		InputPawn = nullptr;
	}
}

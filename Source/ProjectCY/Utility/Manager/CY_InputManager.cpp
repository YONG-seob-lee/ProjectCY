// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_InputManager.h"

#include "CY_BasicGameUtility.h"
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

void UCY_InputManager::RegistAxis(ECY_Axis_Type AxisType, ECY_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event)
{
	if(ActionType == ECY_Action_Type::ActionUpDown)
	{
		UpDownEvent.AxisDelegate = Event;
	}
	else if(ActionType == ECY_Action_Type::ActionLeftRight)
	{
		LeftRightEvent.AxisDelegate = Event;
	}
}

void UCY_InputManager::RegistTouch(ECY_Touch_Event TouchEventType, const FInputTouchBinding& Event)
{
	if(TouchEventType == ECY_Touch_Event::Down)
	{
		TouchDownEvent = Event;
	}
	else if(TouchEventType == ECY_Touch_Event::Up)
	{
		TouchUpEvent = Event;
	}
	else if(TouchEventType == ECY_Touch_Event::Move)
	{
		TouchMoveEvent = Event;
	}
}

void UCY_InputManager::RegistAndroidButton(ECY_AndroidButton_Type ButtonType, const FSimpleDelegate& Delegate)
{
	if(ButtonType == ECY_AndroidButton_Type::Back)
	{
		AndroidBackDelegate = Delegate;
	}
	else if(ButtonType == ECY_AndroidButton_Type::Menu)
	{
		AndroidMenuDelegate = Delegate;
	}
}

void UCY_InputManager::CreateInputPawn()
{
	if(InputPawn != nullptr)
	{
		return;
	}

	InputPawn = Cast<ACY_Pawn_Input>(UCY_BasicGameUtility::SpawnBlueprintActor(TEXT("InputPawn"), FVector::ZeroVector, FRotator::ZeroRotator));
	if(InputPawn)
	{
		InputPawn->Create();
	}
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

void UCY_InputManager::LeftAxisUpDown(float Value)
{
	UpDownEvent.AxisDelegate.Execute(Value);
}

void UCY_InputManager::LeftAxisLeftRight(float Value)
{
	LeftRightEvent.AxisDelegate.Execute(Value);
}

void UCY_InputManager::OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchDownEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UCY_InputManager::OnTouchUp(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchUpEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UCY_InputManager::OnTouchMove(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchMoveEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UCY_InputManager::AndroidBack()
{
	if(AndroidBackDelegate.IsBound())
	{
		AndroidBackDelegate.Execute();
	}
}

void UCY_InputManager::AndroidMenu()
{
	if(AndroidMenuDelegate.IsBound())
	{
		AndroidMenuDelegate.Execute();
	}
}

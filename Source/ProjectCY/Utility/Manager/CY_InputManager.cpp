// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_InputManager.h"

#include "CY_BasicGameUtility.h"
#include "CY_Pawn_Input.h"
#include "CY_Utility.h"

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
	if(AxisType == ECY_Axis_Type::Left)
	{
		if(ActionType == ECY_Action_Type::ActionUpDown)
		{
			CharacterMove_UpDownEvent.AxisDelegate = Event;
		}
		else if(ActionType == ECY_Action_Type::ActionLeftRight)
		{
			CharacterMove_LeftRightEvent.AxisDelegate = Event;
		}	
	}
	else if(AxisType == ECY_Axis_Type::Right)
	{
		if(ActionType == ECY_Action_Type::ActionUpDown)
		{
			CameraMove_UpDownEvent.AxisDelegate = Event;
		}
		else if(ActionType == ECY_Action_Type::ActionLeftRight)
		{
			CameraMove_LeftRightEvent.AxisDelegate = Event;
		}
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

void UCY_InputManager::RegistInteractionButton(const FSimpleDelegate& Delegate)
{
	InteractionDelegate = Delegate;
}

void UCY_InputManager::RegistWorldMapButton(const FSimpleDelegate& Delegate)
{
	WorldMapDelegate = Delegate;
}

void UCY_InputManager::CreateInputPawn()
{
	if(InputPawn != nullptr)
	{
		return;
	}

	InputPawn = Cast<ACY_Pawn_Input>(CY_Utility::SpawnActor(ACY_Pawn_Input::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, TEXT("InputPawn"), ESpawnActorCollisionHandlingMethod::AlwaysSpawn, true));
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
	CharacterMove_UpDownEvent.AxisDelegate.Execute(Value);
}

void UCY_InputManager::LeftAxisLeftRight(float Value)
{
	CharacterMove_LeftRightEvent.AxisDelegate.Execute(Value);
}

void UCY_InputManager::RightAxisUpDown(float Value)
{
	CameraMove_UpDownEvent.AxisDelegate.Execute(Value);
}

void UCY_InputManager::RightAxisLeftRight(float Value)
{
	CameraMove_LeftRightEvent.AxisDelegate.Execute(Value);
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

void UCY_InputManager::Interaction()
{
	if(InteractionDelegate.IsBound())
	{
		InteractionDelegate.Execute();
	}
}

void UCY_InputManager::WorldMap()
{
	if(WorldMapDelegate.IsBound())
	{
		WorldMapDelegate.Execute();
	}
}

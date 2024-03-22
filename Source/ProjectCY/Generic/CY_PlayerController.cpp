// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_PlayerController.h"

ACY_PlayerController::ACY_PlayerController()
{
}

ACY_PlayerController::~ACY_PlayerController()
{
}

void ACY_PlayerController::CreateTouchInterface()
{
	Super::CreateTouchInterface();
}

void ACY_PlayerController::ActivateTouchInterface(UTouchInterface* NewTouchInterface)
{
	Super::ActivateTouchInterface(NewTouchInterface);
}

TObjectPtr<SCY_VirtualJoyStick> ACY_PlayerController::GetVirtualJoyStick() const
{
	if(const TObjectPtr<SVirtualJoystick> JoyStick = VirtualJoystick.Get())
	{
		return static_cast<SCY_VirtualJoyStick*>(JoyStick);
	}
	
	return nullptr;
}

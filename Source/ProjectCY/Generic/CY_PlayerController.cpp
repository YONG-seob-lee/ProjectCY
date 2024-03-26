// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_PlayerController.h"

#include "CY_Define.h"
#include "CY_VirtualJoyStick.h"
#include "GameFramework/InputSettings.h"
#include "Input/CY_TouchInterface.h"
#include "Slate/DeferredCleanupSlateBrush.h"

ACY_PlayerController::ACY_PlayerController()
{
	SetShowMouseCursor(true);
}

ACY_PlayerController::~ACY_PlayerController()
{
}

void ACY_PlayerController::CreateTouchInterface()
{
	const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(Player);

	if(IsValid(LocalPlayer) == false)
	{
		return;
	}

	if(IsValid(LocalPlayer->ViewportClient) && SCY_VirtualJoyStick::ShouldDisplayTouchInterface())
	{
		if(VirtualJoystick.IsValid())
		{
			Cast<ULocalPlayer>(Player)->ViewportClient->RemoveViewportWidgetContent(VirtualJoystick.ToSharedRef());
		}

		if(CurrentTouchInterface == nullptr)
		{
			const FSoftObjectPath& DefaultTouchInterfaceName = GetDefault<UInputSettings>()->DefaultTouchInterface;

			if(DefaultTouchInterfaceName.IsValid())
			{
				const FSoftClassPath& ClassPath = FSoftClassPath(*DefaultTouchInterfaceName.ToString());
				if(ClassPath.IsValid())
				{
					if(const TObjectPtr<UClass> TouchInterfaceClass = Cast<UClass>(ClassPath.TryLoad()))
					{
						CurrentTouchInterface = CY_NewObject<UCY_TouchInterface>(this, TouchInterfaceClass);
					}
				}
			}
		}

		if(CurrentTouchInterface)
		{
			// 조이스틱 생성
			VirtualJoystick = SNew(SCY_VirtualJoyStick);

			// 플레이어 뷰포트에 때려넣음
			LocalPlayer->ViewportClient->AddViewportWidgetContent(VirtualJoystick.ToSharedRef());

			ActivateTouchInterface(CurrentTouchInterface);
		}
	}
}

void ACY_PlayerController::ActivateTouchInterface(UTouchInterface* NewTouchInterface)
{
	if(NewTouchInterface)
	{
		if(VirtualJoystick.IsValid())
		{
			if(const TObjectPtr<SCY_VirtualJoyStick> CY_VirtualJoyStick = static_cast<SCY_VirtualJoyStick*>(VirtualJoystick.Get()))
			{
				if(const TObjectPtr<UCY_TouchInterface> TouchInterface = Cast<UCY_TouchInterface>(NewTouchInterface))
				{
					CY_VirtualJoyStick->ImageCenter = TouchInterface->ImageCenter ? StaticCastSharedRef<ISlateBrushSource>(FDeferredCleanupSlateBrush::CreateBrush(TouchInterface->ImageCenter)) : TSharedPtr<ISlateBrushSource>();
					CY_VirtualJoyStick->CenterImageSize = TouchInterface->CenterImageSize;
					CY_VirtualJoyStick->CenterImageOpacity = TouchInterface->CenterImageOpacity;
					CY_VirtualJoyStick->ImageOuter = TouchInterface->ImageOuter ? StaticCastSharedRef<ISlateBrushSource>(FDeferredCleanupSlateBrush::CreateBrush(TouchInterface->ImageOuter)) : TSharedPtr<ISlateBrushSource>();
					CY_VirtualJoyStick->OuterImageSize = TouchInterface->OuterImageSize;
					CY_VirtualJoyStick->OuterImageOpacity = TouchInterface->OuterImageOpacity;
					CY_VirtualJoyStick->OuterImageSize = TouchInterface->OuterImageSize;
					CY_VirtualJoyStick->Center = TouchInterface->Controls[0].Center;
					CY_VirtualJoyStick->ThumbSize = TouchInterface->Controls[0].ThumbSize;
					CY_VirtualJoyStick->InteractionSize = TouchInterface->Controls[0].InteractionSize;
					CY_VirtualJoyStick->InputScale = TouchInterface->Controls[0].InputScale;
				}
			}
		}
	}
	
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

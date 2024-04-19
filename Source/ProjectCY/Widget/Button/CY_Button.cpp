// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Button.h"
#include "CY_BasicGameUtility.h"

UCY_Button::UCY_Button()
{
}

UCY_Button::~UCY_Button()
{
}

void UCY_Button::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCY_Button::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
}

const FText UCY_Button::GetPaletteCategory()
{
	return FText::FromString("CY Custom");
}

void UCY_Button::SetDelegates()
{
	OnClicked().AddUObject(this, &UCY_Button::OnClick);
	OnPressed().AddUObject(this, &UCY_Button::OnPress);
	OnReleased().AddUObject(this, &UCY_Button::OnRelease);
	OnHovered().AddUObject(this, &UCY_Button::OnHover);
	OnUnhovered().AddUObject(this, &UCY_Button::OnUnhover);
}

void UCY_Button::OnClick()
{
	if (IsUseClockedDelay())
	{
		const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();
		if (!World)
		{
			CY_CHECK(false);
			CY_LOG(TEXT("Wrong Process Please Check CY_Button Class"))
				return;
		}

		const float CurrentClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
		if (LastClickedTime + ClickedDelayTime >= CurrentClickedTime)
		{
			CY_OnClickedInDelayTimeDelegate.Broadcast();
			return;
		}
		LastClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
	}

	if (IsUseLongPressedEvent() == false)
	{
		CY_OnClickedDelegate.Broadcast();
	}
}

void UCY_Button::OnPress()
{
	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = UCY_BasicGameUtility::GetGameWorld()->GetTimerManager();
		TimerManager.SetTimer(PressTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			CY_OnLongPressedDelegate.Broadcast();
		}), LongPressedTime, false);
	}
	CY_OnPressedDelegate.Broadcast();
}

void UCY_Button::OnRelease()
{
	CY_OnReleasedDelegate.Broadcast();

	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = UCY_BasicGameUtility::GetGameWorld()->GetTimerManager();
		if(TimerManager.IsTimerActive(PressTimerHandle))
		{
			TimerManager.ClearTimer(PressTimerHandle);
		}
	}
}

void UCY_Button::OnHover()
{
	CY_OnHoveredDelegate.Broadcast();
}

void UCY_Button::OnUnhover()
{
	CY_OnUnhoveredDelegate.Broadcast();
}
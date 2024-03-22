// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Button.h"

void UCY_Button::SetDelegates()
{
	OnClicked().AddUObject(this, &UCY_Button::OnClick);
	OnPressed().AddUObject(this, &UCY_Button::OnPress);
	OnReleased().AddUObject(this, &UCY_Button::OnReleas);
	OnHovered().AddUObject(this, &UCY_Button::OnHover);
	OnUnhovered().AddUObject(this, &UCY_Button::OnUnhover);
}

void UCY_Button::OnClick()
{
	if (IsUseClockedDelay())
	{
		UWorld* World = GetWorld();
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
		if (IsUseLongPressedEvent() == false)
		{
			CY_OnClickedDelegate.Broadcast();
		}
	}
}

void UCY_Button::OnPress()
{
}

void UCY_Button::OnReleas()
{
}

void UCY_Button::OnHover()
{
}

void UCY_Button::OnUnhover()
{
}
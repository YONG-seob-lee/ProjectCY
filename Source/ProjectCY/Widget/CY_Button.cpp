// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Button.h"

void UCY_Button::SetDelegates()
{
	OnClicked.AddDynamic(this, &UCY_Button::OnClick);
	OnPressed.AddDynamic(this, &UCY_Button::OnPress);
	OnReleased.AddDynamic(this, &UCY_Button::OnReleas);
	OnHovered.AddDynamic(this, &UCY_Button::OnHover);
	OnUnhovered.AddDynamic(this, &UCY_Button::OnUnhover);
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
			OnClickedInDelayTimeDelegate.ExecuteIfBound(this);
			return;
		}
		LastClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
		if (IsUseLongPressedEvent() == false)
		{
			OnClickedDelegate.ExecuteIfBound(this);
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
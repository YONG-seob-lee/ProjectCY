// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Button.h"
#include "CommonTextBlock.h"
#include "CY_BasicGameUtility.h"

UCY_Button::UCY_Button()
{
}

UCY_Button::~UCY_Button()
{
}

void UCY_Button::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
	CPP_CommonText->SetStyle(GetCurrentTextStyleClass());
}

const FText UCY_Button::GetPaletteCategory()
{
	return FText::FromString("CY Custom");
}

void UCY_Button::SetText(const FString& ButtonString) const
{
	if(CPP_CommonText)
	{
		CPP_CommonText->SetText(FText::FromString(ButtonString));
	}
}

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
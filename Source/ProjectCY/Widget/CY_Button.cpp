// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Button.h"
#include "CommonTextBlock.h"
#include "CY_BasicGameUtility.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

UCY_Button::UCY_Button()
{
}

UCY_Button::~UCY_Button()
{
}

void UCY_Button::NativeConstruct()
{
	Super::NativeConstruct();
	CPP_Image_Panel->SetVisibility(bUseButtonImage ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	CPP_ButtonImage->SetVisibility(bUseButtonImage ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	CPP_Text_Panel->SetVisibility(bUseButtonText ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	CPP_CommonText->SetVisibility(bUseButtonText ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
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
	if(CPP_Text_Panel && CPP_CommonText)
	{
		CPP_CommonText->SetText(FText::FromString(ButtonString));
	}
}

void UCY_Button::SetButtonImage(const TObjectPtr<UTexture2D>& ButtonImageTexture2D) const
{
	if(CPP_Image_Panel && CPP_ButtonImage && ButtonImageTexture2D)
	{
		CPP_ButtonImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		CPP_ButtonImage->SetBrushFromTexture(ButtonImageTexture2D);
	}
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
}

void UCY_Button::OnRelease()
{
}

void UCY_Button::OnHover()
{
}

void UCY_Button::OnUnhover()
{
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_TopHud.h"

#include "CY_FadeCommand.h"
#include "CY_FadeSceneTool.h"
#include "CY_Mapper_Hud_TopExpander.h"
#include "CY_SceneManager.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_SystemPopup.h"
#include "Hud_TopExpander.h"
#include "Button/CY_ImageButton.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"

namespace ExpanderAnimation
{
	const FName Open = TEXT("OpenExpander");
	const FName Close = TEXT("CloseExpander");
}

void UCY_Widget_TopHud::InitTopHudWidget()
{
	FillDefaultAnimations();
	
	UCommonButtonBase::FCommonButtonEvent Event;
	Event.AddUObject(this, &UCY_Widget_TopHud::OnClickTopHudButton);
	CPP_TopHudButton->BindTopHudButtonEvent(Event);

	CPP_TopHudExpanderWidget->SetHudData();
	CPP_TopHudExpanderWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UCY_Widget_TopHud::OnClickTopHudButton()
{
	if(IsAnyAnimationPlaying())
	{
		return;
	}
	
	StopAllAnimations();
	
	if(bIsOpenedExpander)
	{
		CPP_TopHudExpanderWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimationByName(ExpanderAnimation::Close);
		bIsOpenedExpander = false;
	}
	else
	{
		CPP_TopHudExpanderWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimationByName(ExpanderAnimation::Open);
		bIsOpenedExpander = true;
	}
}

void UCY_Widget_TopHud::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if(Animation == GetAnimationByName(ExpanderAnimation::Open))
	{
		CPP_TopHudExpanderWidget->SetVisibility(ESlateVisibility::Visible);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void UCY_Widget_TopHudButton::BindTopHudButtonEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	CPP_Button->SetOnClickImageButton(Event);
}

void UCY_Widget_TopHudExpander::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCY_Widget_TopHudExpander::SetHudData()
{
	if(CPP_HorizontalBox == nullptr)
	{
		return;
	}

	const TObjectPtr<UCY_Mapper_Hud_TopExpander> HudTopExpanderMapper = Cast<UCY_Mapper_Hud_TopExpander>(gTableMng.GetTableMapper(ECY_TableDataType::Hud_TopExpander));
	if(HudTopExpanderMapper == nullptr)
	{
		return;
	}

	TMap<FString, TObjectPtr<FHud_TopExpander>> HudExpanderDatas;
	HudTopExpanderMapper->GetExpanderData(HudExpanderDatas);
	
	CPP_HorizontalBox->ClearChildren();

	const TObjectPtr<FHud_TopExpander>* ExpanderData = HudExpanderDatas.Find(ExpanderButtonType::Blank);
	if(ExpanderData == nullptr)
	{
		return;
	}

	const TObjectPtr<UImage> BlankImage = CY_NewObject<UImage>();
	
	const FString ImagePath = gTableMng.GetPath(ECY_TableDataType::BasePath_Img_File, (*ExpanderData)->Image_Path);
	const TObjectPtr<UTexture2D> Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath));

	if(Texture == nullptr)
	{
		return;
	}
	BlankImage->SetBrushFromTexture(Texture);
	CPP_HorizontalBox->AddChild(BlankImage);
	
	for(const auto& HudExpanderData : HudExpanderDatas)
	{
		if(HudExpanderData.Key == ExpanderButtonType::Blank)
		{
			continue;
		}
		
		if(TObjectPtr<UCY_Widget_TopHudExpanderButton> ExpanderButton = Cast<UCY_Widget_TopHudExpanderButton>(gWidgetMng.CreateWidgetNotManagingBySOP(UCY_Widget_TopHudExpanderButton::GetWidgetPath())))
		{
			UCommonButtonBase::FCommonButtonEvent Event;
			Event.AddUObject(this, &UCY_Widget_TopHudExpander::OnClickReturnTitleSceneButton);
			ExpanderButton->BindExpanderButtonEvent(Event);
			CPP_HorizontalBox->AddChild(ExpanderButton);
		}
		
		TObjectPtr<UImage> Blank = BlankImage;
		CPP_HorizontalBox->AddChild(Blank);
	}
}

void UCY_Widget_TopHudExpander::OnClickReturnTitleSceneButton()
{
	if(IsAnyAnimationPlaying())
	{
		return;
	}
	
	FCY_SystemPopupParameter Parameter;
	Parameter.TitleText = TEXT("확인");
	Parameter.bShowExitButton = true;
	Parameter.ContentsText = TEXT("타이틀 화면으로 이동하시겠습니까?");
	Parameter.SelectButtonState = ECY_SelectButtonState::OkCancel;
	Parameter.OnClickConfirmDelegate.AddWeakLambda(this, []()
	{
		CREATE_FADE_COMMAND(Command);
		Command->SetFadeStyle(ECY_FadeStyle::Dialog);
		Command->SetIsDirectFadeOut(false);
		Command->SetLoadingPageType(ECY_LoadingPageType::None);
		Command->OnCheckLoadComplete = FCY_FadeCheckLoadDelegate::CreateLambda([]()
		{
			return gSceneMng.IsCompleteChangeScene();
		});
		
		gWidgetMng.DestroyWidget(UCY_Widget_SystemPopup::GetWidgetName());
		gSceneMng.ChangeScene(ECY_GameSceneType::Title, Command);
	});
	gWidgetMng.ShowSystemPopup(Parameter);
}

void UCY_Widget_TopHudExpanderButton::BindExpanderButtonEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	CPP_ExpanderButton->SetVisibility(ESlateVisibility::Visible);
	CPP_ExpanderButton->SetOnClickImageButton(Event);
}

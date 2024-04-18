// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_NpcInteractionItem.h"

#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_Button.h"
#include "CY_FadeCommand.h"
#include "CY_FadeSceneTool.h"
#include "CY_SceneManager.h"
#include "CY_TableManager.h"
#include "CY_WidgetManager.h"

namespace ItemType
{
	constexpr int32 None = 3; // bubble
	constexpr int32 FastMove = 4;
}

void UCY_Widget_NpcInteractionItem::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	UCommonButtonBase::FCommonButtonEvent Event;
	Event.AddUObject(this , &UCY_Widget_NpcInteractionItem::OnClickInteractionButton);
	CPP_InteractionButton->SetOnClickedDelegate(Event);
}

void UCY_Widget_NpcInteractionItem::SetListItem(const int32 ImageType, const FString& ItemName)
{
	ItemType = ImageType;
	
	SetInteractionItemImage(ImageType);
	SetInteractionItemName(ItemName);
}

void UCY_Widget_NpcInteractionItem::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == DefaultWidgetAnimation::DisAppearance)
	{
		if(OnDisappearanceAnimFinishedCallback)
		{
			OnDisappearanceAnimFinishedCallback(this);
		}
	}
}

void UCY_Widget_NpcInteractionItem::OnClickInteractionButton()
{
	if(ItemType == ItemType::None)
	{
		// Show Toast Message
	}
	else if(ItemType == ItemType::FastMove)
	{
		// Reset Input Keys & Widgets
		if(const TObjectPtr<UCY_BasePlayer> PlayerUnit = Cast<UCY_BasePlayer>(UCY_BasicGameUtility::GetCurrentPlayerUnit()))
		{
			PlayerUnit->SetActionState(ECY_UnitActionState::None);
		
		}
	
		if(const TObjectPtr<UCY_Widget_NpcInteraction> NpcInteractionWidget = gWidgetMng.GetBuiltInWidgetTool()->GetNpcInteractionWidget())
		{
			NpcInteractionWidget->Active(false);
		}

		// Play Fade & Change Scene
		CREATE_FADE_COMMAND(Command);
		Command->SetFadeStyle(ECY_FadeStyle::Drone);
		Command->SetIsDirectFadeOut(false);
		Command->SetLoadingPageType(ECY_LoadingPageType::ShowWorldMap);
		Command->OnCheckLoadComplete = FCY_FadeCheckLoadDelegate::CreateWeakLambda(this, []()
		{
			// 월드맵이 DeActive 될 때 (Camera Fade In 이 끝날 때 월드맵이 활성화 되어있음 활성화가 끝나는 순간이 Fade Out 을 실행할 차례)
			return gWidgetMng.IsFinishedWorldMapProcess();
		});
			            
		gSceneMng.ChangeScene(ECY_GameSceneType::WorldMap, Command);	
	}
}

void UCY_Widget_NpcInteractionItem::SetInteractionItemImage(const int32 ImageType) const
{
	const FString ImagePath = gTableMng.GetPath(ECY_TableDataType::BasePath_Img_File, ImageType);
	if(const TObjectPtr<UTexture2D> ImageTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
	{
		CPP_InteractionButton->SetButtonImage(ImageTexture);
	}
}

void UCY_Widget_NpcInteractionItem::SetInteractionItemName(const FString& ItemName) const
{
	CPP_InteractionButton->SetText(ItemName);
}

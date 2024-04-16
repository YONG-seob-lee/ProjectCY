// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_NpcInteraction.h"

#include "CY_BasicGameUtility.h"
#include "CY_Mapper_NpcContents.h"
#include "CY_TableManager.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_NpcInteractionItem.h"
#include "Components/VerticalBox.h"

void UCY_Widget_NpcInteraction::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UCY_Widget_NpcInteraction::FinishWidget()
{
	Super::FinishWidget();
}

void UCY_Widget_NpcInteraction::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCY_Widget_NpcInteraction::OnNpcInteractionOverlap(int32 NpcUnitId, bool bBegin)
{
	bBegin ? AddNpcInteractionItem(NpcUnitId) : RemoveNpcInteractionItem(NpcUnitId);
}

void UCY_Widget_NpcInteraction::AddNpcInteractionItem(int32 NpcUnitId)
{
	if(CPP_InteractionList == nullptr)
	{
		return;
	}

	const TObjectPtr<UCY_Mapper_NpcContents> NpcContentsMapper = Cast<UCY_Mapper_NpcContents>(gTableMng.GetTableMapper(ECY_TableDataType::Npc_Contents));
	if(NpcContentsMapper == nullptr)
	{
		return;
	}

	TMap<FString, int32> ContentDatas;
	NpcContentsMapper->GetNpcContentDatas(NpcUnitId, ContentDatas);

	for(const auto& ContentData : ContentDatas)
	{
		if(const TObjectPtr<UCY_Widget_NpcInteractionItem> InteractionItem = Cast<UCY_Widget_NpcInteractionItem>(gWidgetMng.CY_CreateWidgetNotManaging(UCY_Widget_NpcInteractionItem::GetWidgetName())))
		{
			InteractionItem->SetListItem(ContentData.Value, ContentData.Key);

			InteractionItems.Emplace(InteractionItem, NpcUnitId);
		
			if(CPP_InteractionList->HasChild(InteractionItem) == false)
			{
				InteractionItem->SetOnDisappearanceAnimFinishedFunc([this](TObjectPtr<UCY_Widget_NpcInteractionItem> Item)
				{
					OnFinishedItemDisappearanceAnim(Item);
				});
				CPP_InteractionList->AddChild(InteractionItem);
			}
		}	
	}
}

void UCY_Widget_NpcInteraction::RemoveNpcInteractionItem(int32 NpcUnitId)
{
	if(CPP_InteractionList == nullptr)
	{
		return;
	}

	for(const auto& InteractionItem : InteractionItems)
	{
		if(InteractionItem.Value == NpcUnitId)
		{
			InteractionItem.Key->PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
		}
	}
}

void UCY_Widget_NpcInteraction::OnFinishedItemDisappearanceAnim(TObjectPtr<UCY_Widget_NpcInteractionItem> FinishedItem)
{
	
#if WITH_EDITOR
	UCY_BasicGameUtility::ShowMessageOnScreen(TEXT("UCY_Widget_NpcInteraction::OnFinishedItemDisappearanceAnim"));
#endif
	
	if(CPP_InteractionList->HasChild(FinishedItem))
	{
		CPP_InteractionList->RemoveChild(FinishedItem);
	}

	InteractionItems.Remove(FinishedItem);
}

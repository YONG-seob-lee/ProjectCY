﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_PreTouchProcessor.h"

#include "CY_BasicGameUtility.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_Touch.h"
#include "Slate/SceneViewport.h"

void FCY_PreTouchProcessor::Initialize()
{
	ChangeTouchEffect(EffectThings::DefaultEffectId);
}

void FCY_PreTouchProcessor::Finalize()
{
	ClearTouchEffect();
}

void FCY_PreTouchProcessor::AddReferencedObjects(FReferenceCollector& Collector)
{
	if(TouchOverlapEffect.Num() > 0)
	{
		Collector.AddReferencedObjects(TouchOverlapEffect);
	}
}

FString FCY_PreTouchProcessor::GetReferencerName() const
{
	return TEXT("FCY_PreTouchProcessor");
}

void FCY_PreTouchProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
	while(TouchEffectQueue.IsEmpty() == false)
	{
		TouchEffectQueue.Pop();		
	}
}

bool FCY_PreTouchProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	FingerCount++;
	
	FingerTouchIndex = MouseEvent.GetPointerIndex();
	CY_LOG(TEXT("FingerTouchIndex = %d"), FingerTouchIndex);	
	
	Touch(MouseEvent.GetScreenSpacePosition());
	return false;
}

bool FCY_PreTouchProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if(FingerCount == 2)
	{
		// MiniMap Zoomin Process
	}
	
	return IInputProcessor::HandleMouseMoveEvent(SlateApp, MouseEvent);
}

bool FCY_PreTouchProcessor::HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	FingerCount--;
	
	TouchOverlapEffect[TouchEffectIndex]->RemoveFromParent();
	TouchOverlapEffect.Remove(TouchEffectIndex);
	TouchOverlapEffect.Emplace(TouchEffectIndex, Cast<UCY_Widget_Touch>(gWidgetMng.CreateWidgetNotManagingBySOP(EffectThings::DefaultTouchEffectPath)));
	
	const int32 PointerIndex = MouseEvent.GetPointerIndex();
	if(FingerTouchIndex != -1 && FingerTouchIndex != MouseEvent.GetPointerIndex())
	{
		SlateApp.RoutePointerUpEvent(FWidgetPath(), FPointerEvent(MouseEvent.GetUserIndex(), PointerIndex,
			FVector2d(-10000.f, -10000.f), FVector2d(-10000.f, -10000), false, false));
		return true;
	}

	TouchEffectQueue.Enqueue(PointerIndex);
	FingerTouchIndex = -1;
	
	return false;
}

void FCY_PreTouchProcessor::UpdateTouchWidget()
{
	for(const auto& TouchEffect : TouchOverlapEffect)
	{
		if(IsValid(TouchEffect.Value))
		{
			TouchEffect.Value->RebuildTouchWidget();
		}
	}
}

void FCY_PreTouchProcessor::CreateTouchEffect()
{
	if(TouchOverlapEffect.Num() > 0)
	{
		ClearTouchEffect();
	}

	for(int32 i = 0 ; i < EffectThings::EffectOverlapMaxCount ; i++)
	{
		TObjectPtr<UCY_Widget_Touch> EffectWidget = Cast<UCY_Widget_Touch>(gWidgetMng.CreateWidgetNotManagingBySOP(EffectThings::DefaultTouchEffectPath));
		if(IsValid(EffectWidget))
		{
			EffectWidget->InitWidget(FName(EffectThings::DefaultTouchEffectPath), false, false);
			EffectWidget->AddToViewport(99999);
			EffectWidget->Active(true);
			TouchOverlapEffect.Emplace(i, EffectWidget);
		}
	}
}

void FCY_PreTouchProcessor::ChangeTouchEffect(int32 TouchEffectId /*  = EffectThings::DefaultEffectId */)
{
	if(TouchEffectId == EffectThings::DefaultEffectId)
	{
		CreateTouchEffect();
		CurrentTouchEffectId = TouchEffectId;
		return;
	}
}

void FCY_PreTouchProcessor::ClearTouchEffect()
{
	for(const auto& TouchEffect : TouchOverlapEffect)
	{
		if(IsValid(TouchEffect.Value))
		{
			TouchEffect.Value->SetVisibility(ESlateVisibility::Collapsed);
			TouchEffect.Value->StopAnimation(EffectThings::Anim);
		}
	}

	TouchOverlapEffect.Empty();
}

void FCY_PreTouchProcessor::Touch(const FVector2d& ScreenPosition)
{
	if(TouchOverlapEffect.Contains(TouchEffectIndex) == false)
	{
		return;
	}

	const FGeometry CachedGeometry = UCY_BasicGameUtility::GetGameViewport()->GetCachedGeometry();
	const FVector2d AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(ScreenPosition);

	TouchOverlapEffect[TouchEffectIndex]->AddToViewport(99999);
	TouchOverlapEffect[TouchEffectIndex]->SetPositionInViewport(AbsoluteScreenPosition);
	TouchOverlapEffect[TouchEffectIndex]->PlayTouch();
	TouchEffectIndex = (TouchEffectIndex + 1) % EffectThings::EffectOverlapMaxCount;


#if WITH_EDITOR
	//UCY_BasicGameUtility::ShowMessageOnScreen(TEXT("FCY_PreTouchProcessor::Touch"));
#endif
}

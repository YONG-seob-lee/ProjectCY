// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_PreTouchProcessor.h"

#include "CY_WidgetManager.h"
#include "CY_Widget_Touch.h"

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
}

bool FCY_PreTouchProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	FingerTouchIndex = MouseEvent.GetPointerIndex();
	const FVector2d ScreenSpacePosition = MouseEvent.GetScreenSpacePosition();


	Touch(ScreenSpacePosition);
	return false;
}

bool FCY_PreTouchProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	return IInputProcessor::HandleMouseMoveEvent(SlateApp, MouseEvent);
}

bool FCY_PreTouchProcessor::HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	return IInputProcessor::HandleMouseButtonUpEvent(SlateApp, MouseEvent);
}

void FCY_PreTouchProcessor::CreateTouchEffect(const FString& TouchEffectWidgetPath)
{
	if(TouchOverlapEffect.Num() > 0)
	{
		ClearTouchEffect();
	}

	for(int32 i = 0 ; i < EffectThings::EffectOverlapMaxCount ; i++)
	{
		TObjectPtr<UCY_Widget> EffectWidget = Cast<UCY_Widget>(gWidgetMng.CreateWidgetNotManagingBySOP(TouchEffectWidgetPath));
		if(IsValid(EffectWidget))
		{
			EffectWidget->InitWidget(FName(TouchEffectWidgetPath), false, false);
			TouchOverlapEffect.Emplace(EffectWidget);
		}
	}
}

void FCY_PreTouchProcessor::ChangeTouchEffect(int32 TouchEffectId /*  = EffectThings::DefaultEffectId */)
{
	if(TouchEffectId == EffectThings::DefaultEffectId)
	{
		CreateTouchEffect(EffectThings::DefaultTouchEffectPath);
		CurrentTouchEffectId = TouchEffectId;
		return;
	}
}

void FCY_PreTouchProcessor::ClearTouchEffect()
{
	for(const auto& TouchEffect : TouchOverlapEffect)
	{
		if(IsValid(TouchEffect))
		{
			TouchEffect->SetVisibility(ESlateVisibility::Collapsed);
			TouchEffect->StopAnimation(EffectThings::Anim);
		}
	}

	TouchOverlapEffect.Empty();
}

void FCY_PreTouchProcessor::Touch(const FVector2d& ScreenPosition)
{
	const TObjectPtr<UCY_Widget> EffectWidget = TouchOverlapEffect[TouchEffectIndex];
	if(IsValid(EffectWidget) == false)
	{
		return;
	}

	EffectWidget->SetPositionInViewport(ScreenPosition);
	EffectWidget->PlayAnimationByName(EffectThings::Anim);
	
	if(const TObjectPtr<UCY_Widget_Touch> TouchWidget = Cast<UCY_Widget_Touch>(EffectWidget))
	{
		TouchWidget->PlayTouch();
	}
	
	TouchEffectIndex = (TouchEffectIndex + 1) % EffectThings::EffectOverlapMaxCount;
}

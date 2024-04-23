// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/IInputProcessor.h"

namespace EffectThings
{
	inline FName Anim = TEXT("Touch_Button_Anim");
	inline FString DefaultTouchEffectPath = TEXT("/Game/Widget/BuiltInWidget/TouchWidget.TouchWidget");

	constexpr int32 DefaultEffectId = 0;
	constexpr int32 EffectOverlapMaxCount = 3;
}

/**
 * 
 */
class PROJECTCY_API FCY_PreTouchProcessor : public IInputProcessor, public FGCObject
{
public:
	void Initialize();
	void Finalize();

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;

	void UpdateTouchWidget();
private:
	void CreateTouchEffect();
	void ChangeTouchEffect(int32 TouchEffectId = EffectThings::DefaultEffectId);
	void ClearTouchEffect();

	void Touch(const FVector2d& ScreenPosition);

	int32 FingerCount = 0;
	
	int32 TouchEffectIndex = 0;
	int32 CurrentTouchEffectId = EffectThings::DefaultEffectId;
	int32 FingerTouchIndex = -1;
	TMap<int32, TObjectPtr<class UCY_Widget_Touch>> TouchOverlapEffect;

	TQueue<int32> TouchEffectQueue;
};
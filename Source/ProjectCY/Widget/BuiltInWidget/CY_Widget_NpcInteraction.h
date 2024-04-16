// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_NpcInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_NpcInteraction : public UCY_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE static FName GetWidgetName() { return TEXT("NpcInteraction"); }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnNpcInteractionOverlap(int32 NpcUnitId, bool bBegin);

private:
	void AddNpcInteractionItem(int32 NpcUnitId);
	void RemoveNpcInteractionItem(int32 NpcUnitId);

	void OnFinishedItemDisappearanceAnim(TObjectPtr<class UCY_Widget_NpcInteractionItem> FinishedItem);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> CPP_InteractionList = nullptr;

	UPROPERTY()
	TMap<TObjectPtr<UCY_Widget_NpcInteractionItem>, int32> InteractionItems;
};

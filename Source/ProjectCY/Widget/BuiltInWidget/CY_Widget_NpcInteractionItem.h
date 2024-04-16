// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_NpcInteractionItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_NpcInteractionItem : public UCY_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE static FName GetWidgetName() { return TEXT("NpcInteractionItem"); }
	FORCEINLINE void SetOnDisappearanceAnimFinishedFunc(const TFunction<void(TObjectPtr<UCY_Widget_NpcInteractionItem>)>& Function) { OnDisappearanceAnimFinishedCallback = Function; }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	
	void SetListItem(const int32 ImageType, const FString& ItemName);

protected:
	virtual void OnAnimFinished(const FName& AnimName) override;
	void OnClickInteractionButton();
private:
	void SetInteractionItemImage(const int32 ImageType) const;
	void SetInteractionItemName(const FString& ItemName) const;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCY_Button> CPP_InteractionButton = nullptr;

	int32 ItemType = 0; 

	TFunction<void(TObjectPtr<UCY_Widget_NpcInteractionItem>)> OnDisappearanceAnimFinishedCallback = nullptr;
};

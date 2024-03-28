// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
#include "CY_Widget.h"
#include "CY_Widget_DialogScreenFader.generated.h"

DECLARE_DELEGATE(FBuiltInFadeDelegate);

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_DialogScreenFader : public UCY_Widget
{
	GENERATED_BODY()

public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath("/Game/Widget/BuiltInWidget/DialogScreenFader.DialogScreenFader"); }
	
	void StartScreenFade(ECY_FadeType _FadeType, const TFunction<void()>& FadeCallback = nullptr);
	
protected:
	virtual void OnAnimFinished(const FName& AnimName) override;
	
private:
	void FinishedFadeIn() const;
	void FinishedFadeOut();
	
	ECY_FadeType FadeType;
	ECY_FadeStatus FadeStatus;

	TFunction<void()> FadeInCompleteCallback;
	TFunction<void()> FadeOutCompleteCallback;
};

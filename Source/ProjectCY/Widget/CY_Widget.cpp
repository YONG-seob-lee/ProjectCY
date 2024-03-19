// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget.h"
#include "CY_Button.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"

void UCY_Widget::NativeConstruct()
{
	MakeButtonPool();
}

void UCY_Widget::NativeDestruct()
{

}

void UCY_Widget::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate /* = true */)
{
	bManaged = _bManaged;

	if(bActivate)
	{
		Active(ResourceWidgetInfo.zOrder);
	}

	SetOriginVisible(GetVisibility());

	InitResourceWidgetInfo();
}

void UCY_Widget::FinishWidget()
{
	if(IsValid(this) == false || this->IsValidLowLevel() == false)
	{
		return;
	}

	
}

void UCY_Widget::Active(int32 _ZOrder /* = 0 */)
{
	if(bAddToViewport == false)
	{
		AddToViewport(_ZOrder == 0 ? ZOrder : _ZOrder);
	}

	if(IsVisible())
	{
		if(IsExistAnim(DefaultWidgetAnimation::Appearance) == true)
		{
			PlayAnimationByName(DefaultWidgetAnimation::Appearance);
		}
	}

	bActive = true;
}

void UCY_Widget::Init()
{
	bActive = false;
	bAddToViewport = false;
}

void UCY_Widget::MakeButtonPool()
{
	if (TObjectPtr<UWidgetTree> WidgetTreePtr = WidgetTree.Get())
	{
		WidgetTreePtr->ForEachWidget([&](UWidget* Widget)
			{
				check(Widget);

				if (Widget->IsA(UCY_Button::StaticClass()))
				{
					UCY_Button* Button = Cast<UCY_Button>(Widget);
					if (Button)
					{
						Buttons.Emplace(Button);
					}
				}
			});
	}
}

void UCY_Widget::PlayAnimationByName(FName Name, float StartTime /* = 0.f */, int32 LoopCount /* = 1 */, EUMGSequencePlayMode::Type PlayType /* = EUMGSequencePlayMode::Forward */,float Speed /* = 1.f */)
{
	
}

TObjectPtr<UWidgetAnimation> UCY_Widget::GetAnimationByName(FName AnimName) const
{
	TObjectPtr<UWidgetAnimation> const* pWidgetAnim = Animations.Find(AnimName);

	return pWidgetAnim == nullptr ? nullptr : *pWidgetAnim;
}

void UCY_Widget::SetOriginVisible(ESlateVisibility _Visibility)
{
	OriginVisibility = _Visibility;
}

void UCY_Widget::InitResourceWidgetInfo()
{
	if(bManaged == false)
	{
		return;
	}

}

bool UCY_Widget::IsExistAnim(FName AnimName) const
{
	const TObjectPtr<UWidgetAnimation> WidgetAnim = GetAnimationByName(AnimName);

	return WidgetAnim != nullptr;
}

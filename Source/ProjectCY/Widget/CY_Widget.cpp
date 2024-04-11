// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget.h"
#include "CY_Button.h"
#include "MovieScene.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"

void UCY_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	MakeButtonPool();
}

void UCY_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCY_Widget::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate /* = true */)
{
	bManaged = _bManaged;

	FillDefaultAnimations();
	
	if(bActivate)
	{
		Active(true);
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

void UCY_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCY_Widget::Active(bool _bActive /* = true */)
{
	if(bAddToViewport == false)
	{
		AddToViewport(_bActive ? ZOrder : 0);
	}
	
	if(IsVisible())
	{
		if(IsExistAnim(DefaultWidgetAnimation::Appearance) == true)
		{
			PlayAnimationByName(DefaultWidgetAnimation::Appearance);
		}
	}

	bActive = _bActive;
}

void UCY_Widget::ActiveDirect(bool _bActive /* = true */)
{
	if(bAddToViewport == false)
	{
		AddToViewport(_bActive ? ZOrder : 0);
	}

	if(IsExistAnim(DefaultWidgetAnimation::AppearanceDirect) == true)
	{
		PlayAnimationByName(DefaultWidgetAnimation::AppearanceDirect);
	}
	
	bActive = _bActive;
}

void UCY_Widget::OnAnimationStarted_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationStarted_Implementation(Animation);
}

void UCY_Widget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	
	OnAnimFinished(FName(Animation->GetMovieScene()->GetName()));
}

void UCY_Widget::Init()
{
	bActive = false;
	bAddToViewport = false;
}

void UCY_Widget::FillDefaultAnimations()
{
	Animations.Empty();

	TObjectPtr<FProperty> Property = GetClass()->PropertyLink;
	while(Property != nullptr)
	{
		if(Property->GetClass() == FObjectProperty::StaticClass())
		{
			if(const TObjectPtr<FObjectProperty> ObjectProperty = CastField<FObjectProperty>(Property))
			{
				if(ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
				{
					TObjectPtr<UWidgetAnimation> WidgetAnimObject = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this));

					if(WidgetAnimObject && WidgetAnimObject->MovieScene != nullptr)
					{
						Animations.Emplace(WidgetAnimObject->GetMovieScene()->GetName(), WidgetAnimObject);
					}
				}
			}
		}
		Property = Property->PropertyLinkNext;
	}
}

void UCY_Widget::MakeButtonPool()
{
	if (const TObjectPtr<UWidgetTree> WidgetTreePtr = WidgetTree.Get())
	{
		WidgetTreePtr->ForEachWidget([&](UWidget* Widget)
			{
				check(Widget);

				if (Widget->IsA(UCY_Button::StaticClass()))
				{
					if (const TObjectPtr<UCY_Button> Button = Cast<UCY_Button>(Widget))
					{
						Buttons.Emplace(Button);
					}
				}
			});
	}
}

void UCY_Widget::PlayAnimationByName(FName Name, float StartTime /* = 0.f */, int32 LoopCount /* = 1 */, EUMGSequencePlayMode::Type PlayType /* = EUMGSequencePlayMode::Forward */,float Speed /* = 1.f */)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(Name))
	{
		PlayAnimation(WidgetAnimation, StartTime, LoopCount, PlayType, Speed);
	}
	
}

TObjectPtr<UWidgetAnimation> UCY_Widget::GetAnimationByName(FName AnimName) const
{
	TObjectPtr<UWidgetAnimation> const* pWidgetAnim = Animations.Find(AnimName);

	return pWidgetAnim == nullptr ? nullptr : *pWidgetAnim;
}

bool UCY_Widget::StopAnimation(const FName& AnimName)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(AnimName))
	{
		UUserWidget::StopAnimation(WidgetAnimation);
		return true;
	}

	return false;
}

void UCY_Widget::SetOriginVisible(ESlateVisibility _Visibility)
{
	OriginVisibility = _Visibility;
}

void UCY_Widget::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == DefaultWidgetAnimation::Appearance)
	{
		PlayIdleAnimation();
	}
}

void UCY_Widget::InitResourceWidgetInfo()
{
	if(bManaged == false)
	{
		return;
	}

}

void UCY_Widget::PlayIdleAnimation()
{
	if(GetAnimationByName(DefaultWidgetAnimation::Idle))
	{
		PlayAnimationByName(DefaultWidgetAnimation::Idle, 0.f, 0);
	}
}

bool UCY_Widget::IsExistAnim(FName AnimName) const
{
	const TObjectPtr<UWidgetAnimation> WidgetAnim = GetAnimationByName(AnimName);

	return WidgetAnim != nullptr;
}

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

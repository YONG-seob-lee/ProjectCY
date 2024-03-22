// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Touch.h"
#include "NiagaraSystemWidget.h"

void UCY_Widget_Touch::PlayTouch() const
{
	if(CCY_TouchEffectWidget)
	{
		CCY_TouchEffectWidget->ActivateSystem(true);
	}
}

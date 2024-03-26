// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Touch.h"
#include "NiagaraSystemWidget.h"
#include "NiagaraUIComponent.h"

void UCY_Widget_Touch::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	if(CPP_TouchEffectWidget)
	{
		CPP_TouchEffectWidget->RebuildWidget();
	}
}

void UCY_Widget_Touch::PlayTouch() const
{
	if(CPP_TouchEffectWidget)
	{
		//CPP_TouchEffectWidget->GetNiagaraComponent()->SetTransformationForUIRendering(ScreenPosition, FVector2f(100.f, 100.f), 1.f);
		CPP_TouchEffectWidget->GetNiagaraComponent()->Activate(true);
	}
}

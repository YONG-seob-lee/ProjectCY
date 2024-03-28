// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Touch.h"

#include "CY_BasicGameUtility.h"
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

void UCY_Widget_Touch::FinishWidget()
{
	Super::FinishWidget();
}

void UCY_Widget_Touch::TouchEvent() const
{
	if(const TObjectPtr<UNiagaraUIComponent> Comp = CPP_TouchEffectWidget->GetNiagaraComponent())
	{
		Comp->Activate(true);
	}

	//PlayAnimation(Touch_Anim);
}

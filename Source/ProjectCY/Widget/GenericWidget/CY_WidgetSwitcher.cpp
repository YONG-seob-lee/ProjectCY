// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_WidgetSwitcher.h"

#include "CY_BasicGameUtility.h"

void UCY_WidgetSwitcher::SetActiveWidgetIndex(int32 Index)
{
	if(bUseWidgetSwitchDelay)
	{
		if(const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld())
		{
			const float CurrentTime = World->GetTimeSeconds(); 	
			if(LastSwitchTime + SwitchDelayTime >= CurrentTime)
			{
				return;
			}

			LastSwitchTime = World->GetTimeSeconds();
		}
	}
	Super::SetActiveWidgetIndex(Index);
}

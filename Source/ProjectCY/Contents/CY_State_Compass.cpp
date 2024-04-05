#include "CY_State_Compass.h"

#include "CY_BasicGameUtility.h"

void UCY_State_Compass::Begin()
{
	Super::Begin();
}

void UCY_State_Compass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnCompass(DeltaTime);
}

void UCY_State_Compass::Exit()
{
	Super::Exit();
}

void UCY_State_Compass::OnCompass(float DeltaTime)
{
	const TObjectPtr<UWorld> GameWorld = UCY_BasicGameUtility::GetGameWorld();
}

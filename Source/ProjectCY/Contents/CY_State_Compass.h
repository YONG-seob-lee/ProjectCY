

#pragma once

#include "CoreMinimal.h"
#include "CY_StateBase.h"
#include "CY_State_Compass.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_State_Compass : public UCY_StateBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

private:
	void OnCompass(float DeltaTime);
};

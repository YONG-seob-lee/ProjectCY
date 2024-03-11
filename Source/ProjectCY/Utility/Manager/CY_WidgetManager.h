// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CY_Singleton.h"
#include "CY_WidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_WidgetManager : public UObject, public UCY_Singleton<UCY_WidgetManager>
{
	GENERATED_BODY()
	
public:
	UCY_WidgetManager();
	~UCY_WidgetManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> WidgetMachine = nullptr;

#define gWidgetMng (*UCY_StateMachine::GetInstance())
};
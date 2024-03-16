// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CY_Singleton.h"
#include "CY_SceneManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_SceneManager : public UObject, public UCY_Singleton<UCY_SceneManager>
{
	GENERATED_BODY()
	
public:

	UCY_SceneManager();
	~UCY_SceneManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	void RegisterSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType) const;

private:
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> SceneStateMachine = nullptr;

	TWeakObjectPtr<class UCY_FadeSceneTool> FadeTool = nullptr;
#define	gSceneMng (*UCY_SceneManager::GetInstance())
};

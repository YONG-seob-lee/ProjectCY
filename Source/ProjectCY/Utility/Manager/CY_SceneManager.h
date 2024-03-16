// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
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

	void RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType) const;

	bool LoadLevelByPath(FCY_LoadLevelInitialized Delegate, const FName& PackagePath = FName(), bool bAbsolute = true);
	void LoadLevelBySoftObjectPtr(TSoftObjectPtr<UWorld> LevelObjectPtr, FCY_LoadLevelInitialized Delegate);
	
	void ChangeScene(ECY_GameSceneType SceneType, const FName& LevelPackagePath = NAME_None);
	void SetSceneBehaviorTreeAsset(TObjectPtr<class UBehaviorTree> BTAsset);
	void RegistSceneBehaviorTree();

	FCY_ChangeSceneDelegate OnChangeScene;
	FCY_LoadLevelDelegate OnStartLevelLoading;
	FCY_LoadLevelDelegate OnFinishedLevelLoading;
	FCY_ChangeSceneState OnCompleteChangeScene;

	FCY_LoadLevelInitialized LoadLevelInitialized;
private:
	bool ChangeSceneStep_LoadLevel();
	void ChangeSceneStep_SetSceneState(uint8 SceneId);
	void OnCompleteLevelLoading(const FString& LevelPackagePath);

	void RegisterSceneBehaviorTree();
	void UnregisterSceneBehaviorTree();
	
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> SceneStateMachine = nullptr;

	UPROPERTY()
	FCY_ChangeSceneData ChangeSceneData;

	UPROPERTY()
	TObjectPtr<class ACY_LevelLogicBase> SceneLogic = nullptr;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> SceneBehaviorTree = nullptr;
	
	UPROPERTY()
	TObjectPtr<class ACY_SceneBT> CustomSceneBT = nullptr;
	
	TWeakObjectPtr<class UCY_FadeSceneTool> FadeTool = nullptr;
#define	gSceneMng (*UCY_SceneManager::GetInstance())
};

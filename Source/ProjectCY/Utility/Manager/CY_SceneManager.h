// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneBase.h"
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

	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float DeltaTime) override;
	
	TObjectPtr<UCY_SceneBase> GetCurrentScene() const;

	FORCEINLINE bool IsCompleteChangeScene() const { return ChangeSceneData.Step == ECY_ChangeSceneStep::Complete; }

	void RegisterScenes() const;
	void SceneLoadComplete(float LoadTime, const FString& LevelName);
	void ExecuteLoadLevelDelegate(const FString& LevelName = TEXT(""));
	
	bool LoadLevelByPath(const FCY_LoadLevelInitialized& Delegate, const FName& PackagePath = FName(), bool bAbsolute = true);
	bool LoadLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld>& LevelObjectPtr, const FCY_LoadLevelInitialized& Delegate);
	
	void ChangeScene(ECY_GameSceneType SceneType, TObjectPtr<class UCY_FadeCommand> Command = nullptr);
	void SetSceneBehaviorTreeAsset(TObjectPtr<class UBehaviorTree> BTAsset);
	void RegistSceneBehaviorTree();

	FCY_ChangeSceneDelegate OnChangeScene;
	FCY_LoadLevelDelegate OnStartLevelLoading;
	FCY_LoadLevelDelegate OnFinishedLevelLoading;
	FCY_ChangeSceneState OnCompleteChangeScene;

	FCY_LoadLevelInitialized LoadLevelInitialized;
private:
	void RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType) const;

	bool ChangeSceneStep_Fade(TObjectPtr<UCY_FadeCommand> Command);
	bool ChangeSceneStep_LoadLevel();
	void ChangeSceneStep_SetSceneState(uint8 SceneId);
	void OnCompleteLevelLoading(const FString& LevelPackagePath);

	void RegisterSceneBehaviorTree();
	void UnregisterSceneBehaviorTree();
	
	
	UPROPERTY()
	TMap<FString, bool> ActiveLevels;
	
	UPROPERTY()
	TObjectPtr<UCY_StateMachine> SceneStateMachine = nullptr;

	UPROPERTY()
	FCY_ChangeSceneData ChangeSceneData;

	UPROPERTY()
	TObjectPtr<class ACY_LevelLogicBase> SceneLogic = nullptr;

	UPROPERTY()
	TObjectPtr<UBehaviorTree> SceneBehaviorTree = nullptr;
	
	UPROPERTY()
	TObjectPtr<class ACY_SceneBT> CustomSceneBT = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UCY_FadeSceneTool> FadeTool = nullptr;
#define	gSceneMng (*UCY_SceneManager::GetInstance())
};

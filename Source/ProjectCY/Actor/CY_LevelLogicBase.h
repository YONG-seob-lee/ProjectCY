// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CY_LevelLogicBase.generated.h"

UCLASS()
class PROJECTCY_API ACY_LevelLogicBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACY_LevelLogicBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool IsSettedBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool StopBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool StartBehaviorTree(bool bLoop = true);

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool PauseBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool IsPausedBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	void RemoveBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool SetBehaviorTree(FString Filename);

	bool SetBehaviorTreeAsset(class UBehaviorTree* _BTAsset);

	UPROPERTY(Category = CY_LevelLogicBase, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTree> BTAsset = nullptr;

	UPROPERTY(Category = CY_LevelLogicBase, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBrainComponent> BrainComponent = nullptr;

	UPROPERTY(Category = CY_LevelLogicBase, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBlackboardComponent> BlackBoardComponent = nullptr;
};

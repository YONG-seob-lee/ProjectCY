// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CY_SceneBT.generated.h"

UCLASS()
class PROJECTCY_API ACY_SceneBT : public AActor
{
	GENERATED_BODY()

public:
	bool CreateBT(const FString& BTPath);
	void DestroyBT();
	void StartBT() const;
	void StopBT() const;
	void PauseBT() const;
	void ResumeBT() const;
	
	ACY_SceneBT();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset = nullptr;
	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> BlackboardComponent = nullptr;
	UPROPERTY()
	TObjectPtr<class UBehaviorTreeComponent> BTComponent = nullptr;
};

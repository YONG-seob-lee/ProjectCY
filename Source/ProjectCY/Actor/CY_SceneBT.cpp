// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneBT.h"

#include "CY_Define.h"
#include "CY_TableDefine.h"
#include "CY_Utility.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


bool ACY_SceneBT::CreateBT(const FString& BTPath)
{
	const FCY_LoadResourceDelegate DummyDelegate;

	BTAsset = Cast<UBehaviorTree>(CY_Utility::LoadObjectFromFile(BTPath, DummyDelegate));
	if(BTAsset == nullptr || BTAsset->BlackboardAsset == nullptr)
	{
		DestroyBT();
		return false;
	}

	if(BlackboardComponent == nullptr)
	{
		BlackboardComponent = NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
		if(BlackboardComponent != nullptr && BlackboardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset) == false)
		{
			DestroyBT();
			return false;
		}

		BlackboardComponent->RegisterComponent();
	}

	BTComponent = CY_NewObject<UBehaviorTreeComponent>(this, TEXT("BTComponent"));
	if(BTComponent == nullptr)
	{
		CY_CHECK(false);
		return false;
	}
	BTComponent->RegisterComponent();
	return true;
}

void ACY_SceneBT::DestroyBT()
{
	if(BTAsset)
	{
		BTAsset = nullptr;
	}
	if(BlackboardComponent)
	{
		BlackboardComponent = nullptr;
	}
	if(BTComponent)
	{
		BTComponent = nullptr;
	}
}

void ACY_SceneBT::StartBT() const
{
	if(!BlackboardComponent || !BTComponent)
	{
		CY_CHECK(false);
		return;
	}

	BTComponent->StartTree(*BTAsset, EBTExecutionMode::SingleRun);
}

void ACY_SceneBT::StopBT() const
{
	if(!BTComponent)
	{
		CY_CHECK(false);
		return;
	}

	BTComponent->StopTree(EBTStopMode::Safe);	
}

void ACY_SceneBT::PauseBT() const
{
	if(!BTComponent)
	{
		CY_CHECK(false);
		return;
	}

	BTComponent->PauseLogic(TEXT("Pause"));
}

void ACY_SceneBT::ResumeBT() const
{
	if(!BTComponent)
	{
		CY_CHECK(false);
		return;
	}

	BTComponent->ResumeLogic(TEXT("Resume"));
}

// Sets default values
ACY_SceneBT::ACY_SceneBT()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACY_SceneBT::BeginPlay()
{
	Super::BeginPlay();
	
}

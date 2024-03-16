// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_LevelLogicBase.h"

#include "BrainComponent.h"
#include "CY_Define.h"
#include "CY_Utility.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


// Sets default values
ACY_LevelLogicBase::ACY_LevelLogicBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACY_LevelLogicBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACY_LevelLogicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACY_LevelLogicBase::IsSettedBehaviorTree()
{
	return BTAsset != nullptr ? true : false;
}

bool ACY_LevelLogicBase::StopBehaviorTree()
{
	if(BTAsset && BrainComponent)
	{
		const FString Reason;
		BrainComponent->StopLogic(Reason);
		return true;
	}
	return false;
}

bool ACY_LevelLogicBase::StartBehaviorTree(bool bLoop)
{
	if(BTAsset == nullptr)
	{
		return false;
	}

	if(BlackBoardComponent == nullptr)
	{
		BlackBoardComponent = CY_NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

		if(BlackBoardComponent != nullptr )
		{
			if(BlackBoardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset) == false)
			{
				RemoveBehaviorTree();
			}
			else
			{
				BlackBoardComponent->RegisterComponent();

				TObjectPtr<UBehaviorTreeComponent> BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
				if(BTComponent == nullptr)
				{
					BTComponent = CY_NewObject<UBehaviorTreeComponent>(this, TEXT("BTComponent"));
					BTComponent->RegisterComponent();
					BrainComponent = BTComponent; 
				}
			}
		}
	}

	return true;
}

bool ACY_LevelLogicBase::PauseBehaviorTree()
{
	if(BrainComponent)
	{
		const TObjectPtr<UBehaviorTreeComponent> BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
		const FString Reason;
		BTComponent->PauseLogic(Reason);
		return true;
	}

	return false;
}

bool ACY_LevelLogicBase::IsPausedBehaviorTree()
{
	if(BrainComponent)
	{
		const TObjectPtr<UBehaviorTreeComponent> BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
		return BTComponent->IsPaused();
	}

	return false;
}

void ACY_LevelLogicBase::RemoveBehaviorTree()
{
	if (BTAsset != nullptr) {
		BTAsset->MarkAsGarbage();
		BTAsset = nullptr;
	}

	if (BrainComponent != nullptr) {
		BrainComponent->Cleanup();
		BrainComponent->DestroyComponent(true);
		BrainComponent = nullptr;
	}

	if (BlackBoardComponent != nullptr) {
		BlackBoardComponent->DestroyComponent(true);
		BlackBoardComponent = nullptr;
	}
}

bool ACY_LevelLogicBase::SetBehaviorTree(FString Filename)
{
	if(BTAsset != nullptr)
	{
		return false;
	}

	const FCY_LoadResourceDelegate DummyDelegate;
	BTAsset = Cast<UBehaviorTree>(CY_Utility::LoadObjectFromFile(Filename, DummyDelegate));
	if(BTAsset == nullptr || BTAsset->BlackboardAsset == nullptr)
	{
		RemoveBehaviorTree();
		return false;
	}

	if(BlackBoardComponent == nullptr)
	{
		BlackBoardComponent = CY_NewObject<UBlackboardComponent>(this, TEXT("LobicBlackBoardComponent"));
		if(BlackBoardComponent != nullptr)
		{
			if(BlackBoardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset) == true)
			{
				const FBlackboard::FKey SelfKey = BTAsset->BlackboardAsset->GetKeyID(FBlackboard::KeySelf);
				if(SelfKey != FBlackboard::InvalidKey)
				{
					BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(SelfKey, this);
				}
			}
			else
			{
				RemoveBehaviorTree();
				return false;
			}

			BlackBoardComponent->RegisterComponent();
		}
	}

	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BehaviorTreeComponent == nullptr)
	{
		BehaviorTreeComponent = CY_NewObject<UBehaviorTreeComponent>(this, TEXT("LogicBehaviorTreeComponent"));
		BehaviorTreeComponent->RegisterComponent();
		BrainComponent = BehaviorTreeComponent;
	}
	else
	{
		RemoveBehaviorTree();
		return false;
	}

	return true;
}

bool ACY_LevelLogicBase::SetBehaviorTreeAsset(UBehaviorTree* _BTAsset)
{
	if (BTAsset == nullptr)
	{
		return false;
	}
	
	if (BTAsset != nullptr)
		{
		RemoveBehaviorTree();
	}

	BTAsset = _BTAsset;
	
	if (BTAsset == nullptr || BTAsset->BlackboardAsset == nullptr)
	{
		RemoveBehaviorTree();
		return false;
	}

	if (BlackBoardComponent == nullptr)
	{
		BlackBoardComponent = CY_NewObject<UBlackboardComponent>(this, TEXT("LogicBlackBoardComponent"));
		if (BlackBoardComponent != nullptr)
		{
			if (BlackBoardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset))
			{
				const FBlackboard::FKey SelfKey = BTAsset->BlackboardAsset->GetKeyID(FBlackboard::KeySelf);
				if (SelfKey != FBlackboard::InvalidKey)
				{
					BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(SelfKey, this);
				}
			}
			else
			{
				RemoveBehaviorTree();
				return false;
			}

			BlackBoardComponent->RegisterComponent();
		}

	}

	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp == nullptr)
	{
		BTComp = CY_NewObject<UBehaviorTreeComponent>(this, TEXT("LogicBrainComponent"));
		BTComp->RegisterComponent();
		BrainComponent = BTComp;
	}
	else
	{
		RemoveBehaviorTree();
		return false;
	}

	return true;
}


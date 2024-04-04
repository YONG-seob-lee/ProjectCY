// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CharacterBase.h"

#include "AnimInstance/CY_AnimInstance.h"
#include "Components/CY_MontageComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CY_CollisionBoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACY_CharacterBase::ACY_CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	
	RootCapsuleComponent = GetCapsuleComponent();
	if(RootCapsuleComponent)
	{
		RootCapsuleComponent->SetCollisionProfileName("Capsule");
		RootCapsuleComponent->BodyInstance.bLockXRotation = true;
		RootCapsuleComponent->BodyInstance.bLockYRotation = true;
	}
	
	RootSkeletalMeshComponent = GetMesh();
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->bUseAttachParentBound = true;
	}

	
	
	RootStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if(RootStaticMeshComponent)
	{
		//RootStaticMeshComponent->SetStaticMesh();
		RootStaticMeshComponent->SetupAttachment(RootComponent);
		RootSkeletalMeshComponent->SetupAttachment(RootStaticMeshComponent);
	}

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	
	MovementComponent = GetCharacterMovement();
	if(MovementComponent)
	{
		MovementComponent->bRunPhysicsWithNoController = true;
		MovementComponent->SetIsReplicated(true);
		MovementComponent->RotationRate = FRotator(0.f, 360.f, 0.f);
		MovementComponent->bOrientRotationToMovement = true;
	}
	
	CreateTestSphere();
}

bool ACY_CharacterBase::Create(const FString& LabelName)
{
	SetName(LabelName);
	SetActorLabel(LabelName);

	Initialize();
	return true;
}

void ACY_CharacterBase::Destory()
{
	CharacterName.Empty();

	Finalize();
}

void ACY_CharacterBase::Initialize()
{
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Activate();

		if(const TObjectPtr<UCY_AnimInstance> _AnimInstance = GetAnimInstance())
		{
			_AnimInstance->Initialize();
		}

		RootSkeletalMeshComponent->bUseAsOccluder = false;
	}
	
	if(RootCapsuleComponent)
	{
		RootCapsuleComponent->Activate();
		RootCapsuleComponent->OnComponentBeginOverlap.Clear();
		RootCapsuleComponent->OnComponentEndOverlap.Clear();	
	}

	if(MovementComponent)
	{
		MovementComponent->Deactivate();
	}

	// Add Anim Instance
	if(const TObjectPtr<UCY_AnimInstance> _AnimInstance = Cast<UCY_AnimInstance>(RootSkeletalMeshComponent->GetAnimInstance()))
	{
		AnimInstance = _AnimInstance;
	}
	
	// Add Anim Montage
	if(const TObjectPtr<UCY_MontageComponent> NewMontageComponent = FindComponentByClass<UCY_MontageComponent>())
	{
		MontageComponent = NewMontageComponent;
		MontageComponent->SetAnimInstance(AnimInstance);
	}

	// Add Collision Box
	CollisionBoxComponent = FindComponentByClass<UCY_CollisionBoxComponent>();
	if(CollisionBoxComponent)
	{
		CollisionBoxComponent->OnComponentBeginOverlap.Clear();
		CollisionBoxComponent->OnComponentEndOverlap.Clear();
	}

	bInitialize = true;
}

void ACY_CharacterBase::Finalize()
{
	if(TestSphere)
	{
		TestSphere->Deactivate();
	}

	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Deactivate();

		if(const TObjectPtr<UCY_AnimInstance> _AnimInstance = GetAnimInstance())
		{
			_AnimInstance->Finalize();
		}
	}
}

TObjectPtr<UCY_AnimInstance> ACY_CharacterBase::GetAnimInstance()
{
	if(RootSkeletalMeshComponent == nullptr)
	{
		return nullptr;
	}

	return AnimInstance ? AnimInstance : Cast<UCY_AnimInstance>(RootSkeletalMeshComponent->GetAnimInstance());
}

void ACY_CharacterBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine)
{
	LodValues.CullDistanceScale = CullDistanceScale;
	LodValues.OutLineCullDistanceScale = OutLineCullDistanceScale;
	LodValues.bVisibleOutLine = bVisibleOutLine;
}

void ACY_CharacterBase::SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const
{
	if(MovementComponent)
	{
		FHitResult Hit(1.f);
		const FVector Delta = Position - GetActorLocation();

		MovementComponent->SafeMoveUpdatedComponent(Delta, Rotator, false, Hit);
	}
}

void ACY_CharacterBase::SetRotator(const FRotator& Rotator) const
{
	if(MovementComponent)
	{
		FHitResult Hit(1.f);
		MovementComponent->SafeMoveUpdatedComponent(FVector::ZeroVector, Rotator, false, Hit);
	}
}

void ACY_CharacterBase::SetActiveMovementComponent(bool bEnable) const
{
	if(MovementComponent)
	{
		MovementComponent->SetActive(bEnable);
	}
}

void ACY_CharacterBase::MoveDirection(const FVector& Direction, float Scale /* = 1.f */, bool bForce /* = false */)
{
	if(MovementComponent)
	{
		//////														   /////
		/// 부드럽게 회전하는 방법이 필요함 ( 어떻게 해야하는지 진짜 모르겠음 ) ///
		/////														   /////
		
		//MovementComponent->AddInputVector(Direction * Scale, bForce);
		AddMovementInput(Direction * Scale);
		SetRotator(FRotationMatrix::MakeFromX(Direction).Rotator());
	}
}

void ACY_CharacterBase::ClearPathFindPoints()
{
	if(PathFindingPoints == -1)
	{
		return;
	}

	PathFindingPoints = -1;
}

void ACY_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACY_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bInitialize == false)
	{
		Initialize();
	}
}

void ACY_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACY_CharacterBase::CreateTestSphere()
{
	TestSphere = CreateDefaultSubobject<USphereComponent>("VisibleTestComponent");
	if(TestSphere)
	{
		TestSphere->SetSphereRadius(500.f);
		TestSphere->SetGenerateOverlapEvents(false);
		TestSphere->SetEnableGravity(false);
		TestSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TestSphere->SetCollisionProfileName(TEXT("NoCollision"));
		TestSphere->SetupAttachment(RootComponent);
		RootSkeletalMeshComponent->SetupAttachment(TestSphere);
		RootStaticMeshComponent->SetupAttachment(TestSphere);
	}
	
}


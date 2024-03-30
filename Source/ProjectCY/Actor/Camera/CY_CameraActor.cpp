// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CameraActor.h"

#include "CY_BasicGameUtility.h"
#include "CY_Utility.h"

ACY_CameraActor::ACY_CameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	if(SceneComponent)
	{
		RootComponent = SceneComponent;
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if(SpringArmComponent)
	{
		SpringArmComponent->SetupAttachment(RootComponent);
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if(CameraComponent)
	{
		CameraComponent->FieldOfView = 90.f;
		CameraComponent->bConstrainAspectRatio = true;
		CameraComponent->AspectRatio = 1.777778f;
		CameraComponent->PostProcessBlendWeight = 1.f;

		CameraComponent->SetupAttachment(SpringArmComponent);
	}
}

bool ACY_CameraActor::Create(const FString& _CameraName, const FVector& Position, const FVector& TargetPosition, float Fov, float AspectRatio, bool bPerspective)
{
	CameraName = _CameraName;
#if WITH_EDITOR
	SetActorLabel(_CameraName);
#endif

	SetTargetPosition(Position, TargetPosition);
	SetFieldOfView(Fov);
	SetAspectRatio(AspectRatio);

	bPerspective ? CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective) : CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

	//CreatePostEffectMaterial();

	return true;
}

void ACY_CameraActor::Destroy()
{
}

void ACY_CameraActor::PreProcess(float DeltaSeconds)
{
}

void ACY_CameraActor::Active(float BlendTime)
{
	const TObjectPtr<APlayerController> PlayerController = UCY_BasicGameUtility::GetPlayerController();
	if(PlayerController == nullptr)
	{
		return;
	}

	if(PlayerController->GetViewTarget() != this)
	{
		BlendTime > 0.f ? PlayerController->SetViewTargetWithBlend(this, BlendTime) : PlayerController->SetViewTarget(this);
	}
}

void ACY_CameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACY_CameraActor::SetTargetPosition(const FVector& CameraVector, const FVector& TargetPosition, float CameraRoll /* = 0.f */)
{
	SetActorLocation(TargetPosition);

	FVector IntervalDistance = TargetPosition - CameraVector;
	SetTargetArmLength(IntervalDistance.Size());

	IntervalDistance.Normalize();
	FRotator Rotator = CY_Utility::MakeRotatorFromForward(IntervalDistance);
	Rotator.Roll = CameraRoll;
	SpringArmComponent->SetWorldRotation(Rotator);
}

void ACY_CameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACY_CameraActor::SetAspectRatio(float AspectRatio) const
{
	if(CameraComponent)
	{
		CameraComponent->SetAspectRatio(AspectRatio);
	}
}

void ACY_CameraActor::SetTargetArmLength(float IntervalDistance) const
{
	MaxIntervalDistance < IntervalDistance ? SpringArmComponent->TargetArmLength = MaxIntervalDistance : SpringArmComponent->TargetArmLength = IntervalDistance;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CameraActor.h"

#include "CY_BasicGameUtility.h"
#include "CY_InputManager.h"

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
		SpringArmComponent->bEnableCameraLag = false;
		SpringArmComponent->bEnableCameraRotationLag = false;
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritYaw = true;
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if(CameraComponent)
	{
		CameraComponent->FieldOfView = 90.f;
		CameraComponent->bConstrainAspectRatio = true;
		CameraComponent->AspectRatio = 1.777778f;
		CameraComponent->PostProcessBlendWeight = 1.f;
		CameraComponent->SetRelativeRotation(FRotator(-23.f, 0.f, 0.f));
		CameraComponent->SetRelativeLocation(FVector(-500.f, 0.f, 0.f));
		CameraComponent->SetupAttachment(SpringArmComponent);
	}
}

void ACY_CameraActor::InitializeInput(const FString& _CameraName)
{
	CameraName = _CameraName;
	SetActorLabel(_CameraName);

	RegistAxis();
}

bool ACY_CameraActor::Create(const FString& _CameraName, const FVector& Position, const FVector& TargetPosition, float Fov, float AspectRatio, bool bPerspective)
{
	CameraName = _CameraName;
#if WITH_EDITOR
	SetActorLabel(_CameraName);
#endif

	//SetTargetPosition(TargetPosition);
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

	CameraMoveProcess();
}

void ACY_CameraActor::SetTargetPosition(const FVector& TargetPosition)
{
	SetActorLocation(TargetPosition);
}

void ACY_CameraActor::SetTargetRotator(const FRotator& TargetRotator)
{
	SetActorRotation(TargetRotator);

	FirstCameraRotator = GetActorRotation();
}

void ACY_CameraActor::RotateCamera()
{
	// FRotator( Pitch : 고개 위아래, Yaw : 고개 좌우, Roll : 이건 무조건 0)
	CachedMovedCameraRotator += FRotator(CameraJoyStickDistance.Y, CameraJoyStickDistance.X, 0.f);
	SetActorRotation(FirstCameraRotator + CachedMovedCameraRotator);
	
	//SpringArmComponent->AddRelativeRotation(FRotator(CameraJoyStickDistance.Y, CameraJoyStickDistance.X, 0.f));
}

void ACY_CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACY_CameraActor::RegistAxis()
{
	FInputAxisUnifiedDelegate UpDownDelegate;
	UpDownDelegate.BindDelegate(this, &ACY_CameraActor::OnAxisUpDown);
	gInputMng.RegistAxis(ECY_Axis_Type::Right, ECY_Action_Type::ActionUpDown, UpDownDelegate);

	FInputAxisUnifiedDelegate LeftRightDelegate;
	LeftRightDelegate.BindDelegate(this, &ACY_CameraActor::OnAxisLeftRight);
	gInputMng.RegistAxis(ECY_Axis_Type::Right, ECY_Action_Type::ActionLeftRight, LeftRightDelegate);
}

void ACY_CameraActor::CameraMoveProcess()
{
	if(CameraJoyStickDistance.Size() > 0.01f)
	{
		RotateCamera();
	}

	CameraJoyStickDistance.X = CameraJoyStickDistance.Y = 0.f;
}

void ACY_CameraActor::OnAxisUpDown(float Value)
{
	if(FMath::IsNearlyEqual(Value, 0.f) == false)
	{
		CameraJoyStickDistance.Y = Value;
	}
}

void ACY_CameraActor::OnAxisLeftRight(float Value)
{
	if(FMath::IsNearlyEqual(Value, 0.f) == false)
	{
		CameraJoyStickDistance.X = Value;
	}
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

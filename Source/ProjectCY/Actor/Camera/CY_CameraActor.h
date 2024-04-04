// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "CY_CameraActor.generated.h"

UCLASS()
class PROJECTCY_API ACY_CameraActor : public AActor
{
	GENERATED_BODY()

public:
	ACY_CameraActor();

	FORCEINLINE CY_Handle GetCameraHandle() const { return CameraHandle; }
	FORCEINLINE FVector GetForward() const { return SpringArmComponent->GetForwardVector(); }
	FORCEINLINE FVector GetCross() const { return SpringArmComponent->GetRightVector(); }
	FORCEINLINE FRotator GetRotation() const { return SpringArmComponent->GetComponentRotation(); }
	FORCEINLINE const FTransform& GetTransform() const { return CameraComponent->GetComponentTransform(); }
	FORCEINLINE void SetCameraAspectRatio(float AspectRatio) const { CameraComponent->SetAspectRatio(AspectRatio); }

	void InitializeInput(const FString& _CameraName);
	
	bool Create(const FString& _CameraName, const FVector& Position, const FVector& TargetPosition, float Fov, float AspectRatio, bool bPerspective = true);
	void Destroy();
	void PreProcess(float DeltaSeconds);
	void Active(float BlendTime = -1.f);

	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetFieldOfView(float FieldOfView) const { CameraComponent->SetFieldOfView(FieldOfView); }
	FORCEINLINE void SetSpringOffset(const FVector& TargetOffset) const { SpringArmComponent->SocketOffset = TargetOffset;  SpringArmComponent->TargetOffset = TargetOffset; }
	FORCEINLINE void SetCameraDistance(float Distance) const { SpringArmComponent->TargetArmLength = Distance; }
	void SetTargetPosition(const FVector& TargetPosition);
	void SetTargetRotator(const FRotator& TargetRotator);
	void RotateCamera();

protected:
	virtual void BeginPlay() override;

	void RegistAxis();

	void CameraMoveProcess();
	
	void OnAxisUpDown(float Value);
	void OnAxisLeftRight(float Value);

	UPROPERTY(Category = ACY_CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent = nullptr;
	
	UPROPERTY(Category = ACY_CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;

	UPROPERTY(Category = ACY_CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

	UPROPERTY(Category = ACY_CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString CameraName;

	UPROPERTY(Category = ACY_CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxIntervalDistance = 99999.f;

private:
	void SetAspectRatio(float AspectRatio) const;
	void SetTargetArmLength(float IntervalDistance) const;
	
	CY_Handle CameraHandle = InvalidUnitHandle;
	FRotator CachedMovedCameraRotator = FRotator::ZeroRotator;
	FRotator FirstCameraRotator = FRotator::ZeroRotator;
	FVector2d CameraJoyStickDistance = FVector2d::ZeroVector;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitDefine.h"
#include "GameFramework/Character.h"
#include "CY_CharacterBase.generated.h"

UCLASS()
class PROJECTCY_API ACY_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACY_CharacterBase();

	bool Create(const FString& LabelName);
	void Destory();

	void Initialize();
	void Finalize();
	
	TObjectPtr<class UCY_AnimInstance> GetAnimInstance();
	
	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine);
	void SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const;
	void SetRotator(const FRotator& Rotator) const;

	void SetActiveMovementComponent(bool bEnable) const;
	void MoveDirection(const FVector& Direction, float Scale = 1.f, bool bForce = false) const;

	void SetStaticMeshComponent(TObjectPtr<UStaticMesh> StaticMesh) const;
	
	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetRootSkeletalMeshComponent() const { return RootSkeletalMeshComponent; }
	FORCEINLINE FVector GetCurrentLocation() const { return GetActorLocation(); }
	FORCEINLINE FRotator GetCurrentRotator() const { return GetActorRotation(); }

	FORCEINLINE bool IsMovePathFindingPoints() const { return PathFindingPoints >= 0; }

	FORCEINLINE void SetOwnerUnitBase(TObjectPtr<class UObject> _UnitBase) { OwnerUnitBase = _UnitBase; } 
	FORCEINLINE TObjectPtr<class UObject> GetOwnerUnitBase() const { return OwnerUnitBase.Get(); }
	
	void ClearPathFindPoints();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void CreateTestSphere();

	FORCEINLINE void SetName(const FString& Name) { CharacterName = Name; }

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString CharacterName = FString();
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> RootSkeletalMeshComponent = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> RootStaticMeshComponent = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RootCapsuleComponent = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> TestSphere = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCY_CharacterLodValues LodValues = FCY_CharacterLodValues();

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCY_MontageComponent> MontageComponent = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> CollisionSphereComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<UCY_AnimInstance> AnimInstance = nullptr;

	TWeakObjectPtr<UObject> OwnerUnitBase = nullptr;
	
	bool bInitialize = false;
	int32 PathFindingPoints = 0;
};

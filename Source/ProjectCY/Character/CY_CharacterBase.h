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
	
	TObjectPtr<class UCY_AnimInstance> GetAnimInstance() const;
	
	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine);
	void SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const;
	
	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetRootSkeletalMeshComponent() const { return RootSkeletalMeshComponent; }
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void CreateCameraComponent();
	void CreateTestSphere();

	FORCEINLINE void SetName(const FString& Name) { CharacterName = Name; }

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString CharacterName = FString();
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> RootSkeletalMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, Transient, Category = Mesh)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> RootStaticMeshComponent = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RootCapsuleComponent = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> PlayerDefaultCamera = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> TestSphere = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCY_CharacterLodValues LodValues = FCY_CharacterLodValues();

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCY_MontageComponent> MontageComponent = nullptr;

	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCY_CollisionBoxComponent> CollisionBoxComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<UCY_AnimInstance> AnimInstance = nullptr;


	bool bInitialize = false;
};

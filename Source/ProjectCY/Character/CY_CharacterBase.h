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

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine);
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCY_CharacterLodValues LodValues;
};

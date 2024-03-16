// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Pawn_Input.h"
#include "CY_InputManager.h"


// Sets default values
ACY_Pawn_Input::ACY_Pawn_Input()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACY_Pawn_Input::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACY_Pawn_Input::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACY_Pawn_Input::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACY_Pawn_Input::Create()
{
	if (InputComponent == nullptr) 
		return false;
	
	const FKey _Key = EKeys::AnyKey;

	// pressed
	FInputKeyBinding KeyBindPressed(FInputChord(_Key, false, false, false, false), EInputEvent::IE_Pressed);
	KeyBindPressed.bConsumeInput = true;
	KeyBindPressed.bExecuteWhenPaused = false;
	KeyBindPressed.KeyDelegate.GetDelegateWithKeyForManualSet().BindWeakLambda(this, [=](const FKey& Key)
	{
		gInputMng.GetBindAllKeysDelegate().ExecuteIfBound(Key, true);
	});
	InputComponent->KeyBindings.Add(KeyBindPressed);

	// released
	FInputKeyBinding KeyBindReleased(FInputChord(_Key, false, false, false, false), EInputEvent::IE_Released);
	KeyBindReleased.bConsumeInput = true;
	KeyBindReleased.bExecuteWhenPaused = false;
	KeyBindReleased.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
	{
		gInputMng.GetBindAllKeysDelegate().ExecuteIfBound(Key, false);
	});
	
	InputComponent->KeyBindings.Add(KeyBindReleased);
	bIsCreated = true;
	return true;
}

void ACY_Pawn_Input::Destroy()
{
	bIsCreated = false;
	InputComponent = nullptr;
}


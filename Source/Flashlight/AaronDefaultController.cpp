// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronDefaultController.h"
#include "EnhancedInputComponent.h"
#include "Aaron.h"
#include "Math/UnrealMathUtility.h"
#include <EnhancedInputSubsystems.h>

void AAaronDefaultController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<AAaron>(aPawn);
	checkf(PlayerCharacter, TEXT("Only AAaron derived classes should only possess AAaron pawns"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnchancedInputComponent."));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem."));

	checkf(InputMappingContent, TEXT("InputMappingContent was not specified"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContent, 0);

	if (ActionMove)
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AAaronDefaultController::HandleMove);

	if (ActionLook)
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &AAaronDefaultController::HandleLook);

}

void AAaronDefaultController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	Super::OnUnPossess();
}

void AAaronDefaultController::HandleMove(const FInputActionValue& InputActionValue)
{
	const float Movement = InputActionValue.Get<float>();

	if (PlayerCharacter)
	{
		
		if(Movement > 0)
			PlayerCharacter->SetActorRotation(FRotator(0, 0, 0));
		if(Movement < 0)
			PlayerCharacter->SetActorRotation(FRotator(0, 180, 0));

		float WalkRotation = -Movement * Speed * 180 / (4000 * PI);


		AActor* LevelObject = PlayerCharacter->GetLevelActor();

		if (LevelObject)
		{
			LevelObject->SetPivotOffset(FVector(0, 4000, 0));
			LevelObject->AddActorLocalRotation(FRotator(0, WalkRotation, 0));
		}
		
	}
}

void AAaronDefaultController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, *(FString::Printf(TEXT("X: %f \nY: %f"), LookAxisVector.X, LookAxisVector.Y)));
	//PlayerCharacter->AddActorLocalRotation(FRotator(LookAxisVector.X, 0, LookAxisVector.Y));
}

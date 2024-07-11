// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronDefaultController.h"
#include "EnhancedInputComponent.h"
#include "Aaron.h"
#include "Math/UnrealMathUtility.h"
#include <EnhancedInputSubsystems.h>
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PrimaryCamera.h"
#include "LevelTerrain.h"

void AAaronDefaultController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<AAaron>(aPawn);
	checkf(PlayerCharacter, TEXT("Only AAaron derived classes should only possess AAaron pawns"));

	CameraReference = PlayerCharacter->FollowCamera;

	CameraStart = SetCameraPosition(CameraHeight);
	
	LevelStart = SetLevelPosition();

	LastCameraPosition = CameraStart;
	CameraReference->SetActorLocation(CameraStart);
	CameraReference->Level->SetActorLocation(CameraStart);

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

	if (ActionJump)
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &AAaronDefaultController::HandleJump);

	if (ActionSprint)
		EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Triggered, this, &AAaronDefaultController::HandleSprint);

	TimeElapsed = 0.f;

}

void AAaronDefaultController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	Super::OnUnPossess();
}

FVector AAaronDefaultController::SetCameraPosition(float Height = 0.f)
{
	FVector Location = PlayerCharacter->GetActorLocation();
	Location.X -= CameraDistance;
	if (CameraStart.Z != NULL)
		Location.Z = CameraStart.Z;
	else
		Location.Z += Height;

	return Location;
}

FVector AAaronDefaultController::SetLevelPosition()
{
	FVector Location = CameraStart;
	Location.Z -= LevelOffset;

	return Location;
}

void AAaronDefaultController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	float Movement = MovementVector.X;
	float Climb = MovementVector.Y;
	float FlashlightAngle;
	FVector2D MousePosition;

	MousePosition = OffsetMouseLocation();
	FlashlightAngle = CalculateLookAngle(MousePosition);


	if (PlayerCharacter)
	{

		if (MousePosition.X > 0)
			PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), Movement);
		else
			PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), -Movement);

		

		//MoveCamera();

		HoldingDown = (Climb < 0);
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Angle: %f"), FlashlightAngle));
		
	}
}

void AAaronDefaultController::HandleLook(const FInputActionValue& InputActionValue)
{
	float FlashlightAngle;
	FVector2D MousePosition;

	MousePosition = OffsetMouseLocation();
	FlashlightAngle = CalculateLookAngle(MousePosition);

	if (PlayerCharacter)
	{
		//MoveCamera();

		if (MousePosition.X > 0)
			PlayerCharacter->SetActorRotation(FRotator(0, 0, 0));
		else
			PlayerCharacter->SetActorRotation(FRotator(0, 180, 0));
		

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Angle: %f"), FlashlightAngle));

		USpotLightComponent* Flashlight = PlayerCharacter->GetFlashlight();
		if (Flashlight)
		{
			Flashlight->SetRelativeRotation(FRotator(FlashlightAngle, 90, 0));
		}

	}
}

void AAaronDefaultController::HandleJump()
{
	if (PlayerCharacter)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Jumped")));
		if (HoldingDown)
		{
			PlayerCharacter->DownJump();
			HoldingDown = false;
		}
		else
			PlayerCharacter->Jump();
	}
}

void AAaronDefaultController::MoveCamera(float DeltaTime, float LerpTime)
{
	if (PlayerCharacter)
	{
		if (TimeElapsed == 0)
		{
			CameraDestination = SetCameraPosition();
			LevelDestination = SetLevelPosition();

		}
		if (TimeElapsed < LerpTime)
		{
			FVector Movement = FMath::Lerp(LastCameraPosition, CameraDestination, TimeElapsed/LerpTime);
			FVector LevelMovement = FMath::Lerp(LastLevelPosition, LevelDestination, TimeElapsed/LerpTime);
			CameraReference->SetActorLocation(Movement);
			CameraReference->Level->SetActorLocation(LevelMovement);
			float LevelRotationDistance = (LastCameraPosition.Y - Movement.Y)/10;
			CameraReference->Level->RotateLevel(4000.f, LevelRotationDistance );
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("rotation distance: %f"), LevelRotationDistance));
			TimeElapsed += DeltaTime;
		}
		else
		{
			LastCameraPosition = CameraDestination;
			LastLevelPosition = LevelDestination;
			TimeElapsed = 0.f;
		}
	}
}


void AAaronDefaultController::HandleSprint()
{	
		UCharacterMovementComponent* CharacterMovement = PlayerCharacter->GetCharacterMovement();
		if (CharacterMovement->MaxWalkSpeed == 600.f)
			CharacterMovement->MaxWalkSpeed = 900.f;
		else
			CharacterMovement->MaxWalkSpeed = 600.f;
}


FVector2D AAaronDefaultController::OffsetMouseLocation()
{
	float MouseX;
	float MouseY;
	int ViewX;
	int ViewY;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);
	GetViewportSize(ViewX, ViewY);

	MouseX = MouseX - ViewX / 2;
	MouseY = ViewY / 2 - MouseY;

	return FVector2D(MouseX, MouseY);
}

float AAaronDefaultController::CalculateLookAngle(FVector2D MousePosition)
{
	return FMath::Atan(MousePosition.Y / abs(MousePosition.X)) * 180 / PI;
}


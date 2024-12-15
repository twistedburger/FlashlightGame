// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AaronDefaultController.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class AAaron;
class APrimaryCamera;
class UUserWidget;


UCLASS(Abstract)
class AAaronDefaultController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionInteract = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContent = nullptr;

	UPROPERTY(EditAnywhere, Category= "Player Input|Character Movement")
	float Speed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraDistance = 900.f;

	void MoveCamera(float DeltaTime, float LerpTime);
	FVector LastCameraPosition;
	FVector CameraDestination;
	FVector LastLevelPosition;
	FVector LevelDestination;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraHeight = 0.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float LevelOffset = 200.f;

protected:
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleSprint();
	void HandleJump();
	void HandleInteract();


	bool HoldingDown = false;

	FVector2D OffsetMouseLocation();
	float CalculateLookAngle(FVector2D MousePosition);

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	APrimaryCamera* CameraReference;
	FVector CameraStart;
	FVector LevelStart;

	float TimeElapsed;

	FVector GetCameraPosition(float Height);
	FVector GetLevelPosition();


private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;


	UPROPERTY()
	AAaron* PlayerCharacter = nullptr;

};
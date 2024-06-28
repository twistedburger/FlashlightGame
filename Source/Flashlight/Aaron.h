// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aaron.generated.h"

UCLASS()
class FLASHLIGHT_API AAaron : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AAaron();

	UPROPERTY(EditAnywhere, Category = "Path")
	float Radius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(float AxisVal);

	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};

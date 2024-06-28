// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aaron.generated.h"

UCLASS()
class FLASHLIGHT_API AAaron : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAaron();
	float Radius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

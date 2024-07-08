// Fill out your copyright notice in the Description page of Project Settings.

#define _USE_MATH_DEFINES
#include "Aaron.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "math.h"


// Sets default values
AAaron::AAaron()
{

	Radius = 900.f;


	bUseControllerRotationYaw = false;


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAaron::BeginPlay()
{

	Super::BeginPlay();

	Flashlight = GetComponentByClass<USpotLightComponent>();
	
}


USpotLightComponent* AAaron::GetFlashlight()
{
	if (Flashlight)
		return Flashlight;
	else
		return nullptr;
}

AActor* AAaron::GetLevelActor()
{
	if (Level)
		return Level;
	else 
		return nullptr;
}

// Called every frame
void AAaron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAaron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Aaron.h"

// Sets default values
AAaron::AAaron()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAaron::BeginPlay()
{
	
	Radius = 500;
	Super::BeginPlay();
	
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
	PlayerInputComponent->BindAxis(TEXT("Move"), this, &AAaron::Move);
}

void AAaron::Move(float AxisVal)
{
	AddMovementInput(GetActorForwardVector() * AxisVal);
}

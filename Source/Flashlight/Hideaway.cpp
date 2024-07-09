// Fill out your copyright notice in the Description page of Project Settings.


#include "Hideaway.h"

// Sets default values
AHideaway::AHideaway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FString AHideaway::ReactToTrigger()
{
	return "This is a hideaway!";
}

// Called when the game starts or when spawned
void AHideaway::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHideaway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


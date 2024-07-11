// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTerrain.h"

// Sets default values
ALevelTerrain::ALevelTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALevelTerrain::RotateLevel(float Radius, float DistanceTravelled)
{
	float WalkRotation = DistanceTravelled * 180 / (Radius * PI);
	AddActorLocalRotation(FRotator(0, WalkRotation, 0));
}

// Called when the game starts or when spawned
void ALevelTerrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


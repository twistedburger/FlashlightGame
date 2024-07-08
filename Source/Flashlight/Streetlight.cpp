// Fill out your copyright notice in the Description page of Project Settings.


#include "Streetlight.h"

// Sets default values
AStreetlight::AStreetlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StreetlightType = "";

}

// Called when the game starts or when spawned
void AStreetlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStreetlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


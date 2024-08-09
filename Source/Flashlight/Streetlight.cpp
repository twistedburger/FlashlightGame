// Fill out your copyright notice in the Description page of Project Settings.


#include "Streetlight.h"
#include "Components/BoxComponent.h"

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
	Collider = GetComponentByClass<UBoxComponent>();
	Collider->SetGenerateOverlapEvents(true);
	
}

// Called every frame
void AStreetlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AStreetlight::ReactToTrigger()
{
	return StreetlightType;
}

bool AStreetlight::IsLightSource()
{
	return true;
}


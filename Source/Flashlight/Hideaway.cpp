// Fill out your copyright notice in the Description page of Project Settings.


#include "Hideaway.h"
#include "Aaron.h"

// Sets default values
AHideaway::AHideaway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AHideaway::CheckIfHideaway()
{
	return true;
}

void AHideaway::PerformAction(AActor* Character)
{
	if (AAaron* Aaron = Cast<AAaron>(Character)) {
		Aaron->SetHideaway(this);
	}
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


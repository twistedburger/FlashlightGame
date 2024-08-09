// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryAIController.h"
#include "NavigationSystem.h"


void APrimaryAIController::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = GetPawn()->GetActorLocation();
	EndingLocation = StartingLocation;
	EndingLocation.Y += PatrolDistance;
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	Patrol();
}

void APrimaryAIController::Patrol()
{
	FVector CurrentLocation = GetPawn()->GetActorLocation();
	CurrentLocation.X = 0;
	GetPawn()->SetActorLocation(CurrentLocation);

	FVector Destination = CurrentLocation;
	
	if (CurrentLocation.Y <= StartingLocation.Y)
		Destination.Y += PatrolTolerance;
	else if (CurrentLocation.Y <= EndingLocation.Y)
		Destination.Y += (PatrolDistance - PatrolTolerance);
	else
		Destination.Y -= (PatrolDistance + PatrolTolerance);

	MoveToLocation(Destination);

}


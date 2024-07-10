// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryAIController.h"
#include "NavigationSystem.h"


void APrimaryAIController::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = GetPawn()->GetActorLocation();
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	Patrol();
}

void APrimaryAIController::Patrol()
{
	FVector CurrentLocation = GetPawn()->GetActorLocation();
	FVector Destination = CurrentLocation;
	float Tolerance = 20;
	if (CurrentLocation.Y <= StartingLocation.Y + Tolerance)
		Destination.Y += 600;
	else
		Destination.Y -= 600;
		
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Y: %f"), CurrentLocation.Y));
	MoveToLocation(Destination);




	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("StartingLocation: X: %f, Y: %f\nCurrentLocation: X: %f, Y: %f\nNewLocation: X: %f, Y: %f"), StartingLocation.X, StartingLocation.Y, CurrentLocation.X, CurrentLocation.Y, NewLocation.X, NewLocation.Y));
	/*MoveToLocation(Location);*/
}


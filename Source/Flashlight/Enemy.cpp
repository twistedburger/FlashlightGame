// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PrimaryAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Aaron.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Vision = GetComponentByClass<UBoxComponent>();
	Vision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPlayerDetectedOverlapBegin);
	Vision->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnPlayerDetectedOverlapEnd);

	Attack = GetComponentByClass<USphereComponent>();
	Attack->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPlayerAttackOverlapBegin);
	Attack->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnPlayerAttackOverlapEnd);

	PrimaryAIController = Cast<APrimaryAIController>(GetController());
	PrimaryAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AEnemy::OnAIMoveCompleted);

	Speech = GetComponentByClass<UWidgetComponent>();
	ToggleAlert();
	
}

void AEnemy::ToggleAlert()
{
	if (Speech)
		Speech->ToggleVisibility(true);

}

void AEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	PrimaryAIController->Patrol();
}

void AEnemy::MoveToPlayer()
{
	FVector AaronLocation = Aaron->GetActorLocation();
	AaronLocation.X = 0;
	
	PrimaryAIController->MoveToLocation(AaronLocation, StoppingDistance, true);
}

void AEnemy::SeekPlayer()
{

	MoveToPlayer();
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this, &AEnemy::SeekPlayer, 0.25f, true);
}

void AEnemy::StopSeekingPlayer()
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(AlertTimerHandle) > 0)
	{
	ToggleAlert();
	GetWorld()->GetTimerManager().ClearTimer(AlertTimerHandle);
	}
	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);
	
}

void AEnemy::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAaron* AaronRef = Cast<AAaron>(OtherActor)) 
	{

		Speech->ToggleVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(AlertTimerHandle, this, &AEnemy::ToggleAlert, 0.75f, false);
		Aaron = AaronRef;
		PlayerDetected = true;
		if(Aaron->GetActorLocation().X < 5)
			SeekPlayer();
	}
}

void AEnemy::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AAaron* AaronRef = Cast<AAaron>(OtherActor))
	{
		PlayerDetected = false;
		StopSeekingPlayer();
		PrimaryAIController->Patrol();
	}
}

void AEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAaron* AaronRef = Cast<AAaron>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "DEAD");
	}
}

void AEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


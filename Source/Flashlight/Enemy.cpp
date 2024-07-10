// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PrimaryAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Vision = GetComponentByClass<UBoxComponent>();
	Attack = GetComponentByClass<UCapsuleComponent>();
}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();


	PrimaryAIController = Cast<APrimaryAIController>(GetController());
	PrimaryAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AEnemy::OnAIMoveCompleted);
	
}

void AEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{

		PrimaryAIController->Patrol();


}

void AEnemy::MoveToPlayer()
{
}

void AEnemy::SeekPlayer()
{
}

void AEnemy::StopSeekingPlayer()
{
}

void AEnemy::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AEnemy::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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


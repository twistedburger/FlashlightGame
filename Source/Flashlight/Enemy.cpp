// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PrimaryAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Aaron.h"
#include "Components/WidgetComponent.h"
#include "PrimaryInterface.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	Apprehend = GetComponentByClass<USphereComponent>();
	Apprehend->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPlayerCaught);

	PrimaryAIController = Cast<APrimaryAIController>(GetController());
	PrimaryAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AEnemy::OnAIMoveCompleted);

	TArray<UActorComponent*> SpeechOptions =  K2_GetComponentsByClass(UWidgetComponent::StaticClass());

	for (int32 i = 0; i < SpeechOptions.Num(); i++)
	{
		UWidgetComponent* tempWidget = Cast<UWidgetComponent>(SpeechOptions[i]);
		FString name = tempWidget->GetName();

		if (tempWidget->GetName() == "SpeechBubble")
			Speech = tempWidget;
		else if(tempWidget->GetName() == "LostVision")
			LostSight = tempWidget;
	}

	ToggleAlert();
	ToggleHmm();
	Pondering = false;

	GetCharacterMovement()->MaxWalkSpeed = EnemyWalkingSpeed;
	
}

void AEnemy::ToggleAlert()
{
	if (Speech)
		Speech->ToggleVisibility(true);
}

void AEnemy::ToggleHmm()
{
	if (LostSight)
		LostSight->ToggleVisibility(true);
}

void AEnemy::RestartPatrol()
{
	Pondering = false;
	PrimaryAIController->Patrol();
}

void AEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if(!Pondering)
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
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this, &AEnemy::SeekPlayer, ChaseTimer, true);
}

void AEnemy::StopSeekingPlayer()
{
	if (PlayerDetected)
	{
		Pondering = true;
		PrimaryAIController->StopMovement();
		GetWorld()->GetTimerManager().SetTimer(PonderTimerHandle, this, &AEnemy::RestartPatrol, PonderTimer, false, PonderTimer);
		PlayerDetected = false;
	}

	if (GetWorld()->GetTimerManager().GetTimerRemaining(AlertTimerHandle) > 0)
	{
		ToggleAlert();
		GetWorld()->GetTimerManager().ClearTimer(AlertTimerHandle);
	}

	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);

	if (!LostSight->GetVisibleFlag())
		ToggleHmm();
}

void AEnemy::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAaron* AaronRef = Cast<AAaron>(OtherActor)) 
	{
		Speech->ToggleVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(AlertTimerHandle, this, &AEnemy::ToggleAlert, AlertDisplayTimer, false);

		Aaron = AaronRef;
		PlayerDetected = true;

		
		if(Aaron->GetActorLocation().X < HidingTolerance)
			SeekPlayer();
	}
}

void AEnemy::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AAaron* AaronRef = Cast<AAaron>(OtherActor))
	{
		GetWorld()->GetTimerManager().SetTimer(HmmTimerHandle, this, &AEnemy::ToggleHmm, AlertDisplayTimer, false);
		StopSeekingPlayer();
	}
}

void AEnemy::OnPlayerCaught(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAaron* AaronRef = Cast<AAaron>(OtherActor))
	{
		//Implement player getting caught
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "DEAD");
	}
	else if (IPrimaryInterface* OverlappedObject = Cast<IPrimaryInterface>(OtherActor))
	{
		if (OverlappedObject->IsLightSource())
		{
			GetWorld()->GetTimerManager().SetTimer(HmmTimerHandle, this, &AEnemy::ToggleHmm, AlertDisplayTimer, false);
			StopSeekingPlayer();
		}
	}
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


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PrimaryInterface.h"
#include "Enemy.generated.h"

class APrimaryAIController;
class UBoxComponent;
class USphereComponent;
class AAaron;
class UWidgetComponent;

UCLASS()
class FLASHLIGHT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();


	APrimaryAIController* PrimaryAIController;

	AAaron* Aaron;

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

	UBoxComponent* Vision;
	USphereComponent* Apprehend;

	UPROPERTY(EditAnywhere, Category = "SpeechBubble")
	UWidgetComponent* Speech;
	UPROPERTY(EditAnywhere, Category = "SpeechBubble")
	UWidgetComponent* LostSight;

	UPROPERTY(EditAnywhere)
	float StoppingDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float EnemyWalkingSpeed = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Chasing")
	float ChaseTimer = 0.25f;

	UPROPERTY(EditAnywhere, Category = "Chasing")
	float PonderTimer = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Chasing")
	float AlertDisplayTimer = 0.75f;


	FTimerHandle SeekPlayerTimerHandle;
	FTimerHandle AlertTimerHandle;
	FTimerHandle HmmTimerHandle;
	FTimerHandle PonderTimerHandle;

	bool PlayerDetected;

	UFUNCTION()
	void MoveToPlayer();

	UFUNCTION()
	void SeekPlayer();

	UFUNCTION()
	void StopSeekingPlayer();

	UFUNCTION()
	void OnPlayerDetectedOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerDetectedOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void OnPlayerCaught(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ToggleAlert();
	void ToggleHmm();
	void RestartPatrol();
	bool Pondering;
	float HidingTolerance = 5.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};

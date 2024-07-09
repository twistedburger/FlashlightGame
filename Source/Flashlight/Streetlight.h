// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrimaryInterface.h"
#include "Streetlight.generated.h"

class UBoxComponent;

UCLASS()
class FLASHLIGHT_API AStreetlight : public AActor, public IPrimaryInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStreetlight();

	UPROPERTY(EditAnywhere, Category="Identification")
	FString StreetlightType;
	UBoxComponent* Collider;

	FString GetType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrimaryInterface.h"
#include "Hideaway.generated.h"

UCLASS()
class FLASHLIGHT_API AHideaway : public AActor, public IPrimaryInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHideaway();
	virtual bool CheckIfHideaway() override;
	void PerformAction(AActor* Character = nullptr) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PrimaryAIController.generated.h"

class UNavigationSystemV1;

/**
 * 
 */
UCLASS()
class FLASHLIGHT_API APrimaryAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	FVector StartingLocation;
	FVector EndingLocation;
	

	UFUNCTION()
	void Patrol();

protected:

private:
	UNavigationSystemV1* NavArea;

	FVector RandomLocation;
};

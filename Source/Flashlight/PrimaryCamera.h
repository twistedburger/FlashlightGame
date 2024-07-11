// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PrimaryCamera.generated.h"

class ALevelTerrain;

/**
 * 
 */
UCLASS()
class FLASHLIGHT_API APrimaryCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Level")
	ALevelTerrain* Level = nullptr;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpingPlatform.generated.h"

class UStaticMeshComponent;

	UCLASS()
class FLASHLIGHT_API AJumpingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpingPlatform();

	UPROPERTY(EditAnywhere, Category = "Type")
	bool IsFloating = false;

	void EnablePlatform();
	void DisablePlatform();

	UStaticMeshComponent* PlatformMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

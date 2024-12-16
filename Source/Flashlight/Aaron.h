// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputActionValue.h>
#include "Dialog.h"
#include "Aaron.generated.h"

class USpotLightComponent;
class UCapsuleComponent;
class UBoxComponent;
class AJumpingPlatform;
class AAaronDefaultController;
class APrimaryCamera;


UCLASS()
class FLASHLIGHT_API AAaron : public ACharacter
{
	GENERATED_BODY()

private:
	

public:
	// Sets default values for this character's properties
	AAaron();

	UPROPERTY(EditAnywhere, Category = "Camera")
	APrimaryCamera* FollowCamera = nullptr;

	UPROPERTY(EditAnywhere, Category = "Jump")
	AJumpingPlatform* CurrentPlatform = nullptr;

	USpotLightComponent* GetFlashlight();


	UPROPERTY(VisibleAnywhere)
	bool IsHidden;

	AAaronDefaultController* AaronController;

	UPROPERTY(EditAnywhere, Category="LERP")
	float LerpTime =0.72f;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	ADialog* dialog = nullptr;


protected:
	UFUNCTION()
	void Hit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlatform(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void NotOnPlatform(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Leave(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void DownJump();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Flashlight")
	USpotLightComponent* Flashlight = nullptr;
	
	UCapsuleComponent* PrimaryCollider = nullptr;
	UBoxComponent* PlatformCollider = nullptr;
	
	float ZLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	ADialog* getDialog();

};

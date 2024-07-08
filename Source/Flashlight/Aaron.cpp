// Fill out your copyright notice in the Description page of Project Settings.

#define _USE_MATH_DEFINES
#include "Aaron.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "math.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AAaron::AAaron()
{

	Radius = 900.f;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArm->SetupAttachment(GetMesh());
	CameraArm->TargetArmLength = Radius;
	CameraArm->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAaron::BeginPlay()
{

	Super::BeginPlay();

	Flashlight = GetComponentByClass<USpotLightComponent>();
	Collider = GetComponentByClass<UCapsuleComponent>();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAaron::Hit);
	
}

void AAaron::Hit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit")));
}


USpotLightComponent* AAaron::GetFlashlight()
{
	if (Flashlight)
		return Flashlight;
	else
		return nullptr;
}


// Called every frame
void AAaron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAaron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


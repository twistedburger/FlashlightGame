// Fill out your copyright notice in the Description page of Project Settings.

#define _USE_MATH_DEFINES
#include "Aaron.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "math.h"


// Sets default values
AAaron::AAaron()
{

	Radius = 900.f;

	//CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraArm->SetupAttachment(GetMesh());
	//CameraArm->TargetArmLength = Radius;
	//CameraArm->bUsePawnControlRotation = false;

	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	//FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

USpotLightComponent* AAaron::GetFlashlight()
{
	if (Flashlight)
		return Flashlight;
	else
		return nullptr;
}

// Called when the game starts or when spawned
void AAaron::BeginPlay()
{

	Super::BeginPlay();

	Flashlight = GetComponentByClass<USpotLightComponent>();


	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	PlayerController->SetShowMouseCursor(true);
	//	PlayerController->SetInputMode(FInputModeGameAndUI());
	//}
	
}


AActor* AAaron::GetLevelActor()
{
	if (Level)
		return Level;
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
	//check(PlayerInputComponent);
	//PlayerInputComponent->BindAxis("Move", this, &AAaron::Move);

}

//void AAaron::Move(float AxisVal)
//{
//	if (Controller != NULL && AxisVal != 0.0)
//	{
//		//Turn();
//
//		AddMovementInput(GetActorRightVector() * AxisVal);
//		float WalkRotation = AxisVal * 180 / (Radius * M_PI);
//		AddActorLocalRotation(FRotator(0, WalkRotation, 0));
//	}
//
//}
//
//void AAaron::Look(const FInputActionValue& Value)
//{
//	FVector2D LookAxisVector = Value.Get<FVector2D>();
//	AddActorLocalRotation(FRotator(LookAxisVector.X, 0, LookAxisVector.Y));
//
//}
//
//
//void AAaron::Turn()
//{
//	if (Direction)
//	{
//	CameraArm->bUsePawnControlRotation = true;
//	Direction = false;
//	GetMesh()->AddLocalRotation(FRotator(0, 180, 0));
//
//	}
//}
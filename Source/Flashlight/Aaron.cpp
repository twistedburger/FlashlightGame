// Fill out your copyright notice in the Description page of Project Settings.

#define _USE_MATH_DEFINES
#include "Aaron.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "math.h"
#include "Streetlight.h"
#include "JumpingPlatform.h"
#include "AaronDefaultController.h"
#include "Camera/CameraActor.h"

// Sets default values
AAaron::AAaron()
{

	Radius = 900.f;

	/*CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArm->SetupAttachment(GetMesh());
	CameraArm->TargetArmLength = Radius;
	CameraArm->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;*/

	ZLocation = GetActorLocation().Z;

	

	bUseControllerRotationYaw = false;


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = -1;
	AActor::SetActorTickEnabled(true);

	IsHidden = false;

	GetCharacterMovement()->JumpZVelocity = 400.f;

}

// Called when the game starts or when spawned
void AAaron::BeginPlay()
{

	Super::BeginPlay();

	Flashlight = GetComponentByClass<USpotLightComponent>();
	PrimaryCollider = GetComponentByClass<UCapsuleComponent>();
	PrimaryCollider->SetGenerateOverlapEvents(true);
	PrimaryCollider->OnComponentBeginOverlap.AddDynamic(this, &AAaron::Hit);
	PrimaryCollider->OnComponentEndOverlap.AddDynamic(this, &AAaron::Leave);
	
	PlatformCollider = GetComponentByClass<UBoxComponent>();
	PlatformCollider->SetGenerateOverlapEvents(true);
	PlatformCollider->OnComponentBeginOverlap.AddDynamic(this, &AAaron::OnPlatform);
	PlatformCollider->OnComponentEndOverlap.AddDynamic(this, &AAaron::NotOnPlatform);

	AaronController = Cast<AAaronDefaultController>(GetController());
}

void AAaron::Hit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (IPrimaryInterface* OverlappedObject = Cast<IPrimaryInterface>(OtherActor))
	{
	FString Type = OverlappedObject->ReactToTrigger();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Type);
	if (OverlappedObject->CheckIfHideaway())
		IsHidden = true;
	if(IsHidden)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Hidden");

	}
	//if(AStreetlight* Streetlight = Cast<AStreetlight>(OtherActor))
	//{
	//	FString Type = Streetlight->GetType();
	//	
	//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Type);
	//	IsHidden = true;
	//}

}

void AAaron::OnPlatform(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AJumpingPlatform* Platform = Cast<AJumpingPlatform>(OtherActor))
	{
		CurrentPlatform = Platform;
		CurrentPlatform->EnablePlatform();
	}
}

void AAaron::NotOnPlatform(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AJumpingPlatform* Platform = Cast<AJumpingPlatform>(OtherActor))
	{
		Platform->DisablePlatform();
		CurrentPlatform = nullptr;
	}
}

void AAaron::Leave(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IPrimaryInterface* OverlappedObject = Cast<IPrimaryInterface>(OtherActor))
	{
		if (OverlappedObject->CheckIfHideaway())
			IsHidden = false;
	}
}


void AAaron::DownJump()
{
	if (CurrentPlatform)
	{
		CurrentPlatform->DisablePlatform();
	}
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
	
	if(FollowCamera)
		AaronController->MoveCamera(DeltaTime, LerpTime);



	//FString hidden = IsHidden ? "True" : "False";
	float velocity = GetVelocity().Y;
	GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Red, FString::Printf(TEXT("%f"), velocity));
}

// Called to bind functionality to input
void AAaron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


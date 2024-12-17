// Fill out your copyright notice in the Description page of Project Settings.


#include "Aaron.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Streetlight.h"
#include "JumpingPlatform.h"
#include "AaronDefaultController.h"
#include "Camera/CameraActor.h"

// Sets default values
AAaron::AAaron()
{

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
	OverlappedObject->PerformAction(this);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Type);
	if (OverlappedObject->CheckIfHideaway())
		IsHidden = true;
		//dialog->NextDialog();
		//dialog->ShowDialog();
	}
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
}

// Called to bind functionality to input
void AAaron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

ADialog* AAaron::getDialog()
{
	return dialog;
}

bool AAaron::InDialog()
{
	return Speaking;
}

void AAaron::SetDialog(bool IsSpeaking)
{
	Speaking = IsSpeaking;
}

void AAaron::StartDialog(TEnumAsByte<Conversations> conversation)
{
	if (!Speaking) {
		Speaking = true;
		dialog->StartDialog(conversation);
	}
}


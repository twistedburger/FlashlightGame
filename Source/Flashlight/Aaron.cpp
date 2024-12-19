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

void AAaron::AnimateHide(float DeltaTime)
{
	int CrouchMultiplier = 20;
	float CrouchMin = 0;
	float CrouchMax = 10;
	if (IsHidden && CrouchPosition < CrouchMax) {
		CrouchPosition += CrouchMultiplier * DeltaTime;
		CrouchPosition = CrouchPosition >= CrouchMax ? CrouchMax : CrouchPosition;
	}
	else if (!IsHidden && CrouchPosition > CrouchMin) {
		CrouchPosition -= CrouchMultiplier * DeltaTime;
		CrouchPosition = CrouchPosition <= CrouchMin ? CrouchMin : CrouchPosition;
	}
	/*if (IsHidden && CrouchPosition >= CrouchMax)
		IsCrouched = true;
	else if (!IsHidden && CrouchPosition <= CrouchMin)
		IsCrouched = false;*/
	if (IsHidden && NearbyHideaway) {
		MoveBehindBox(NearbyHideaway->GetActorLocation());
	}
	else if (IsHidden) {
		MoveFromBox();
	}
}

void AAaron::MoveBehindBox(FVector box)
{
	float BoxWidth = 100;
	float Tolerance = 20;
	float HiddenLocation = 230;
	FVector PlayerPosition = GetActorLocation();
	FVector BoxEdge = box;
	BoxEdge.Y -= BoxWidth;
	if (PlayerPosition.Y < BoxEdge.Y) {
		SetActorRotation(FRotator(0, 0, 0));
	}
	else {
		SetActorRotation(FRotator(0, 180, 0));
	}
	if (abs(PlayerPosition.Y - BoxEdge.Y) > Tolerance) {
		AddMovementInput(GetActorRightVector());
	} else {
		SetActorRotation(FRotator(0, 270, 0));
		if ((HiddenLocation - PlayerPosition.X) > Tolerance) {
			AddMovementInput(GetActorRightVector());
		}
		else {
			PlayerPosition.X = HiddenLocation;
			PlayerPosition.Y = BoxEdge.Y;
			SetActorLocation(PlayerPosition);
			IsCrouched = true;
		}
	}
}

void AAaron::MoveFromBox()
{
	float Tolerance = 10;
	float PathLocation = 0;
	FVector PlayerPosition = GetActorLocation();

	SetActorRotation(FRotator(0, 90, 0));
	if (PlayerPosition.X > Tolerance) {
		AddMovementInput(GetActorRightVector());
	}
	else {
		PlayerPosition.X = PathLocation;
		SetActorLocation(PlayerPosition);
		IsHidden = false;
		ToggleMovement(true);
		IsCrouched = false;
		Flashlight->SetVisibility(true, true);


	}


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


void AAaron::Hide()
{
	if (!IsHidden && IsNearHideaway) {
		IsHidden = true;
		ToggleMovement(false);
		Flashlight->SetVisibility(false, true);
	}
	else {
		NearbyHideaway = nullptr;
	}
}

void AAaron::SetHideaway(AActor* Hideaway)
{
	NearbyHideaway = Hideaway;
}

void AAaron::ToggleMovement(bool Movement)
{
	if (AaronController) {
		if (Movement)
			AaronController->EnableMovement();
		else
			AaronController->DisableMovement();
	}
}


void AAaron::Hit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (IPrimaryInterface* OverlappedObject = Cast<IPrimaryInterface>(OtherActor))
	{
	FString Type = OverlappedObject->ReactToTrigger();
	OverlappedObject->PerformAction(this);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Type);
	if (OverlappedObject->CheckIfHideaway()) {
		IsNearHideaway = true;
	}
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
		{
			IsNearHideaway = false;
		}
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
	AnimateHide(DeltaTime);
	if(FollowCamera)
		AaronController->MoveCamera(DeltaTime, LerpTime);	
}

// Called to bind functionality to input
void AAaron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AAaron::GetCrouchPosition()
{
	return CrouchPosition;
}

ADialog* AAaron::getDialog()
{
	return dialog;
}

bool AAaron::InDialog()
{
	return Speaking;
}

bool AAaron::NearHideaway()
{
	return IsNearHideaway;
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


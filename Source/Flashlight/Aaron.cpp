// Fill out your copyright notice in the Description page of Project Settings.


#include "Aaron.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAaron::AAaron()
{

	Radius = 500.f;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> characterMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/01_Main/Meshes/SKM_Manny.SKM_Manny'"));
	if (characterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(characterMesh.Object);
	}

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArm->SetupAttachment(GetMesh());
	CameraArm->TargetArmLength = Radius;
	CameraArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAaron::BeginPlay()
{

	Super::BeginPlay();
	
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
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &AAaron::Move);
}

void AAaron::Move(float AxisVal)
{
	if(Controller != NULL && AxisVal != 0.0)
	AddMovementInput(GetActorRightVector() * AxisVal);
}

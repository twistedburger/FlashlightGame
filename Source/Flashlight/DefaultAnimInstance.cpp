// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAnimInstance.h"
#include "GameFramework/Character.h"
#include "Aaron.h"

UDefaultAnimInstance::UDefaultAnimInstance()
{
}

void UDefaultAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AAaron>(TryGetPawnOwner());
}

void UDefaultAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character)
	{
		UpdateAnimProperties();
		
	}
}

void UDefaultAnimInstance::UpdateAnimProperties()
{
	WalkSpeed = abs(Character->GetVelocity().Size());
	CrouchPosition = Character->GetCrouchPosition();
	IsHidden = Character->IsHidden;
	IsCrouched = Character->IsCrouched;
}


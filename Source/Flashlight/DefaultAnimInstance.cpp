// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAnimInstance.h"
#include "GameFramework/Character.h"

UDefaultAnimInstance::UDefaultAnimInstance()
{
}

void UDefaultAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(TryGetPawnOwner());
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
	
	WalkSpeed = abs(Character->GetVelocity().Y);
}

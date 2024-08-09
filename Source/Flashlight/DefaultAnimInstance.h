// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefaultAnimInstance.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class FLASHLIGHT_API UDefaultAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDefaultAnimInstance();

	ACharacter* Character;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void UpdateAnimProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

private:

};

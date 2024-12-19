// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefaultAnimInstance.generated.h"

class AAaron;
class UBlendSpace1D;

/**
 * 
 */
UCLASS()
class FLASHLIGHT_API UDefaultAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDefaultAnimInstance();

	AAaron* Character;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void UpdateAnimProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool IsHidden = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool IsCrouched = false;


private:

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "PrimaryInterface.h"
#include "Dialog.h"
#include "DialogTrigger.generated.h"


/**
 * 
 */
UCLASS()
class FLASHLIGHT_API ADialogTrigger : public ATriggerVolume, public IPrimaryInterface
{
	GENERATED_BODY()

public:
	ADialogTrigger();
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TEnumAsByte<Conversations> Trigger = Conversations::Beach;
	void PerformAction(AActor* character = nullptr) override;
	
};

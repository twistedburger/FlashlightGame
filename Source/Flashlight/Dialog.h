// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dialog.generated.h"


UCLASS()
class FLASHLIGHT_API ADialog : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialog();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialog")
	class UDialogWidget* DialogWidget = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowDialog();
	void HideDialog();
	void NextDialog();

private:
	TArray<FString> Dialogs;
	int DialogCounter = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialog.h"
#include "DialogWidget.h"
#include "Components/TextBlock.h"
#include "Containers/Array.h"

// Sets default values
ADialog::ADialog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADialog::BeginPlay()
{
	Super::BeginPlay();
	Dialogs.Add(TEXT("Look a beach!"));
	Dialogs.Add(TEXT("Great spot for a fire"));
	Dialogs.Add(TEXT("Vroom Vroom"));
	ShowDialog();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Dialogs[0]);
	
	
}

// Called every frame
void ADialog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialog::ShowDialog()
{
	if (DialogWidget) {
		DialogWidget->AddToViewport();
		if (DialogCounter < Dialogs.Num())
			DialogWidget->DisplayText(FText::FromString(Dialogs[DialogCounter]));
	}
}

void ADialog::HideDialog()
{
	if (DialogWidget) {
		DialogWidget->RemoveFromViewport();
	}
}

void ADialog::NextDialog()
{
	DialogCounter++;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Current counter: %d"), DialogCounter));
}



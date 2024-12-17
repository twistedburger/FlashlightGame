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
	BeachDialogs.Add(TEXT("Look a beach!"));
	BeachDialogs.Add(TEXT("Great spot for a fire"));
	BeachDialogs.Add(TEXT("Vroom Vroom"));
	SpaceShipDialogs.Add(TEXT("I'm a little spaceship!"));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, Dialogs[0]);
	
	
}

// Called every frame
void ADialog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialog::StartDialog(Conversations conversation)
{
	switch (conversation) {
	case Conversations::Beach:
		Dialogs = BeachDialogs;
		BeachDialogs.Empty();
		break;
	case Conversations::Spaceship:
		Dialogs = SpaceShipDialogs;
		SpaceShipDialogs.Empty();
		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("ERROR: NO DIALOG SCENE."));
	}
	ShowDialog();
	NextDialog();	
}

void ADialog::ShowDialog()
{
	if (DialogWidget) {
		DialogWidget->AddToViewport();
		
	}
}

void ADialog::HideDialog()
{
	if (DialogWidget) {
		DialogWidget->RemoveFromViewport();
	}
}

bool ADialog::NextDialog()
{
	if (DialogCounter < Dialogs.Num()) {
		DialogWidget->DisplayText(FText::FromString(Dialogs[DialogCounter]));
		DialogCounter++;
		return true;
	}
	else {
		DialogCounter = 0;
		Dialogs.Reset();
		HideDialog();
		return false;
	}
}



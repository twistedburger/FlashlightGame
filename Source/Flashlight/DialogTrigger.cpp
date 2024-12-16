// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTrigger.h"
#include "Dialog.h"
#include "Aaron.h"

ADialogTrigger::ADialogTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADialogTrigger::PerformAction(AActor* character)
{
	if (AAaron* Aaron = Cast<AAaron>(character)) {
		ADialog* AaronDialog = Aaron->getDialog();
		AaronDialog->NextDialog();
		AaronDialog->ShowDialog();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include "Components/TextBlock.h"

void UDialogWidget::NativeConstruct() {
	Super::NativeConstruct();

}

void UDialogWidget::DisplayText(FText TextToDisplay)
{
	if (Text)
	{
		Text->SetText(TextToDisplay);
	}
}

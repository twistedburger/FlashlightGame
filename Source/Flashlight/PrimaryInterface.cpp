// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryInterface.h"

// Add default functionality here for any IPrimaryInterface functions that are not pure virtual.

FString IPrimaryInterface::ReactToTrigger()
{
	return "";
}

bool IPrimaryInterface::CheckIfHideaway()
{
	return false;
}

bool IPrimaryInterface::IsLightSource()
{
	return false;
}

void IPrimaryInterface::PerformAction(AActor* character)
{
}



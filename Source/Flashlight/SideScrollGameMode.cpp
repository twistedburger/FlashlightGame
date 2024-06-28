// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollGameMode.h"
#include "Aaron.h"

ASideScrollGameMode::ASideScrollGameMode()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;

    DefaultPawnClass = AAaron::StaticClass();
}
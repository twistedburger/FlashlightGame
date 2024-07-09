// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpingPlatform.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AJumpingPlatform::AJumpingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void AJumpingPlatform::EnablePlatform()
{
	if (PlatformMesh)
	{
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AJumpingPlatform::DisablePlatform()
{
	if (PlatformMesh && IsFloating)
	{
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void AJumpingPlatform::BeginPlay()
{
	Super::BeginPlay();
	PlatformMesh = GetComponentByClass<UStaticMeshComponent>();
	checkf(PlatformMesh, TEXT("Unable to get reference to the Platform Mesh."));
	if(IsFloating)
		DisablePlatform();

}

// Called every frame
void AJumpingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


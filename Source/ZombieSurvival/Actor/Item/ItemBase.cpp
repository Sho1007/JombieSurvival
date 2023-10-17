// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include <Components/StaticMeshComponent.h>

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
}

void AItemBase::Interact(AActor* InteractActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact : %s Interact to %s"), *InteractActor->GetName(), *GetName());
}

void AItemBase::Init(ASpawnManager* NewSpawnManager)
{
	if (NewSpawnManager) SpawnManager = NewSpawnManager;
}

void AItemBase::Activate()
{
	bIsActived = true;
	SetActorTickEnabled(bIsActived);
	SetActorHiddenInGame(!bIsActived);
	StaticMeshComponent->SetCollisionProfileName(TEXT("DroppedItem"));
	StaticMeshComponent->SetSimulatePhysics(bIsActived);
}

void AItemBase::Deactivate()
{
	bIsActived = false;
	SetActorTickEnabled(bIsActived);
	SetActorHiddenInGame(!bIsActived);
	StaticMeshComponent->SetSimulatePhysics(bIsActived);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

bool AItemBase::IsActive() const
{
	return bIsActived;
}
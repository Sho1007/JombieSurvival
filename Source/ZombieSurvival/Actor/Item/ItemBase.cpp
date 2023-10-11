// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include <Components/StaticMeshComponent.h>

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	StaticMeshComponent->SetCollisionProfileName(TEXT("DroppedItem"));
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetSimulatePhysics(true);
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::Interact(AActor* InteractActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact : %s Interact to %s"), *InteractActor->GetName(), *GetName());
}
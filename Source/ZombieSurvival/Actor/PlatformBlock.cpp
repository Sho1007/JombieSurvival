// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/PlatformBlock.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <NavModifierComponent.h>

#include "Character/Player/PlayerBase.h"

// Sets default values
APlatformBlock::APlatformBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifierComponent"));

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformBlock::OnBeginOverlap);
}

// Called when the game starts or when spawned
void APlatformBlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformBlock::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("APlatformBlock::BoxComponentBeginOverlap"));
	if (APlayerBase* Player = Cast<APlayerBase>(OtherActor))
	{
		FVector Location = GetActorLocation();
		FVector TargetLocation = OtherActor->GetActorLocation();
		if (FMath::Abs(Location.X - TargetLocation.X) > FMath::Abs(Location.Y - TargetLocation.Y))
		{
			// Vertical
			if (Location.X > TargetLocation.X)
			{
				UE_LOG(LogTemp, Warning, TEXT("APlatformBlock::Top"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("APlatformBlock::Bottom"));
			}
		}
		else
		{
			// Horizontal
			if (Location.Y > TargetLocation.Y)
			{
				UE_LOG(LogTemp, Warning, TEXT("APlatformBlock::Right"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("APlatformBlock::Left"));
			}
		}
	}
}
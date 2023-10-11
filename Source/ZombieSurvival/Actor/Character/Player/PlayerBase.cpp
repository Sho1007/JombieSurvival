// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/PlayerBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

#include "../../../Interface/InteractInterface.h"
#include "../../Weapon/GunBase.h"
#include "../Enemy/ZombieBase.h"

APlayerBase::APlayerBase()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerBase::OnComponentBeginOverlap);

	VisibleArea = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	VisibleArea->SetupAttachment(RootComponent);
	VisibleArea->OnComponentEndOverlap.AddDynamic(this, &APlayerBase::OnVisibleAreaEndOverlap);
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon_R"));
		Gun->SetOwner(this);
	}
}

void APlayerBase::EarnMoeny_Implementation(int32 NewMoneyAmount)
{
	MoneyAmount += NewMoneyAmount;
	UE_LOG(LogTemp, Warning, TEXT("APlayerBase::EarnMoeny) MoneyAmount : %d"), MoneyAmount);
}

void APlayerBase::AddBullet_Implementation(int32 NewBulletAmount)
{
	// Todo : Add Bullet To Weapon
	Gun->AddBullet(NewBulletAmount);
	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::AddBullet) BulletAmount : %d"), BulletAmount);
}

void APlayerBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractInterface* Interface = Cast<IInteractInterface>(OtherActor))
	{
		Interface->Interact(this);
	}
}

void APlayerBase::OnVisibleAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::OnVisibleAreaEndOverlap) Overlaped Actor : %s"), *OtherActor->GetName());
	/*if (AZombieBase* Zombie = Cast<AZombieBase>(OtherActor))
	{
		Zombie->Respawn();
	}*/
}
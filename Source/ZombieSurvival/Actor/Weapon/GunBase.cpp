// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/GunBase.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/DamageEvents.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/ArrowComponent.h>

#include "../SpawnManager.h"
#include "../Character/Player/PlayerBase.h"

#include "ProjectileBase.h"

AGunBase::AGunBase()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(SkeletalMeshComponent);

	MuzzleArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleArrowComponent"));
	MuzzleArrowComponent->SetupAttachment(SkeletalMeshComponent);
}

void AGunBase::AddBullet(int32 NewBulletAmount)
{
	this->BulletAmount += NewBulletAmount;

	UE_LOG(LogTemp, Warning, TEXT("AGunBase::AddBullet) BulletAmount : %d"), BulletAmount);
}

void AGunBase::BeginPlay()
{
	Super::BeginPlay();

	// Init SpawnManager
	SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(this, ASpawnManager::StaticClass()));
}

void AGunBase::SetPlayer(APlayerBase* NewPlayer)
{
	Player = NewPlayer;
}

void AGunBase::SetDamage(float NewDamage)
{
	WeaponDamage = NewDamage;
}

EGunType AGunBase::GetGunType() const
{
	return GunType;
}

void AGunBase::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("AGunBase::Attack"));
	Super::Attack();

	if (GetOwner() == NULL) return;
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (this->BulletAmount <= 0) return;
		this->BulletAmount--;

		Player->PlayFireMontage();

		//if (GunFireClass) GetWorld()->SpawnActor<AActor>(GunFireClass, MuzzleArrowComponent->GetComponentLocation(), FRotator::ZeroRotator);
		
		FireBullet();

		if (GunFireSound) UGameplayStatics::PlaySound2D(GetWorld(), GunFireSound);
	}
}

void AGunBase::FireBullet()
{
	// Todo : Bullet Variation to use BulletName
	SpawnManager->SpawnProjectile(MuzzleArrowComponent->GetComponentLocation(), MuzzleArrowComponent->GetComponentRotation(), TEXT(""));
}
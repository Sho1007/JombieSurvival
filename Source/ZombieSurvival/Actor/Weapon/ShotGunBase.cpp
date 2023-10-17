// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/ShotGunBase.h"

#include <Components/ArrowComponent.h>
#include <Engine/DamageEvents.h>

#include "ShotGunHitBox.h"
#include "../Character/Enemy/ZombieBase.h"
#include "../Character/Player/PlayerBase.h"

void AShotGunBase::BeginPlay()
{
	Super::BeginPlay();

	if (ShotGunHitBoxClass) ShotGunHitBox = GetWorld()->SpawnActor<AShotGunHitBox>(ShotGunHitBoxClass);
	if (ShotGunHitBox)
	{
		ShotGunHitBox->AttachToComponent(MuzzleArrowComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		ShotGunHitBox->SetActorRelativeLocation(FVector(150, 0, 0));
		ShotGunHitBox->SetActorRelativeRotation(FRotator(90, 0, 0));
		ShotGunHitBox->SetActorScale3D(FVector(3, 3, 3));
		ShotGunHitBox->Init(this);
	}
}

void AShotGunBase::FireBullet()
{
	ShotGunHitBox->Fire();
}

void AShotGunBase::ApplyDamage(AActor* TargetActor)
{
	if (AZombieBase* Zombie = Cast<AZombieBase>(TargetActor))
	{
		Zombie->TakeDamage(WeaponDamage, FDamageEvent(UDamageType::StaticClass()), Player->GetController(), ShotGunHitBox);
	}
}
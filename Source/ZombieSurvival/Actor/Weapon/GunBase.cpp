// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/GunBase.h"

#include <GameFramework/Character.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/DamageEvents.h>

void AGunBase::AddBullet(int32 NewBulletAmount)
{
	this->BulletAmount += NewBulletAmount;

	UE_LOG(LogTemp, Warning, TEXT("AGunBase::AddBullet) BulletAmount : %d"), BulletAmount);
}

void AGunBase::Attack()
{
	Super::Attack();

	if (GetOwner() == NULL) return;
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (this->BulletAmount <= 0) return;
		this->BulletAmount--;
		
		//UE_LOG(LogTemp, Warning, TEXT("AGunBase::Attack) Bullet Amount : %d"), BulletAmount);
		FHitResult OutHit;
		FVector Start = OwnerCharacter->GetActorLocation() + (OwnerCharacter->GetMesh()->GetRightVector() * 50.0f);
		FVector End = Start + (OwnerCharacter->GetMesh()->GetRightVector() * AttackRange);
		FCollisionObjectQueryParams Params;
		Params.AddObjectTypesToQuery(ECC_PhysicsBody);

		TArray<AActor*> IgnoreActorArray;
		IgnoreActorArray.Add(OwnerCharacter);
		if (GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, Params))
		{
			//UE_LOG(LogTemp, Warning, TEXT("AGunBase::Attack) Hit Actor : %s, Bone Name : %s"), *OutHit.GetActor()->GetName(), *OutHit.BoneName.ToString());

			OutHit.GetActor()->TakeDamage(WeaponDamage, FDamageEvent(UDamageType::StaticClass()), OwnerCharacter->GetController(), this);
		}
	}
}
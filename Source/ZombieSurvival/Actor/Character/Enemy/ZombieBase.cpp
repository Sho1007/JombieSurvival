// Fill out your copyright notice in the Description page of Project Settings.


#include "../Enemy/ZombieBase.h"

#include <Engine/DamageEvents.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

#include "../../Weapon/WeaponBase.h"
#include "../../Item/ItemBase.h"
#include "../../SpawnManager.h"

AZombieBase::AZombieBase(const FObjectInitializer& ObjectInitializer)
{
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("BlockOnlyCapsule"));

	this->GetMesh()->SetCollisionProfileName(TEXT("TraceOnlyMesh"));
}

void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Tick) Called"));
}

void AZombieBase::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Attack Called"));

	if (bIsAttacking == false)
	{
		bIsAttacking = true;

		StopMoving();

		PlayAnimMontage(AttackMontage);
	}
}

void AZombieBase::CheckHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Attack Called"));

	FHitResult OutHit;
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * AttackRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Pawn, Params))
	{
		//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CheckHit) Hitted Actor : %s"), *OutHit.GetActor()->GetName());
		OutHit.GetActor()->TakeDamage(AttackDamage, FDamageEvent(UDamageType::StaticClass()), GetController(), this);
	}
}

void AZombieBase::StartMoving()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AZombieBase::StopMoving()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

float AZombieBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::TakeDamage) %f"), DamageAmount);


	if (AWeaponBase* WeaponBase = Cast<AWeaponBase>(DamageCauser))
	{
		if (bIsKnockBackable)
		{
			bIsAttackable = false;
			bIsAttacking = false;
			StopMoving();
			StopAnimMontage();
			if (HittedMontage) PlayAnimMontage(HittedMontage);
			AddActorWorldOffset(GetActorForwardVector() * -WeaponBase->GetKnockbackPower(), false, nullptr, ETeleportType::ResetPhysics);
		}

		Health -= DamageAmount;

		if (Health <= 0.0f)
		{
			DropItem();

			this->Disactive();
		}
	}

	return 0.0f;
}

void AZombieBase::DropItem()
{
	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		GetWorld()->SpawnActor<AItemBase>(ItemArray[i], GetActorLocation(), FRotator::ZeroRotator);
	}
}

void AZombieBase::Disactive()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Disactive"));
	bIsActived = false;
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	GetCharacterMovement()->GravityScale = 0;

	//Cast<AAIController>(GetController())->GetBrainComponent()->StopLogic(TEXT("Actor Disactived"));
}

void AZombieBase::Active()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Active"));
	bIsActived = true;
	SetActorTickEnabled(true);
	StopAnimMontage();
	bIsAttackable = false;
	bIsAttacking = false;
	
	this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("BlockOnlyCapsule"));

	this->GetMesh()->SetCollisionProfileName(TEXT("TraceOnlyMesh"));

	GetCharacterMovement()->GravityScale = 1;

	Health = MaxHealth;

	StartMoving();

	SetActorHiddenInGame(false);
}

bool AZombieBase::IsActive() const
{
	return bIsActived;
}

void AZombieBase::Init(APlayerBase* NewPlayer, ASpawnManager* NewSpawnManager, int NewObjectIndex)
{
	SpawnManager = NewSpawnManager;
	ObjectIndex = NewObjectIndex;

	Player = NewPlayer;
}

void AZombieBase::Respawn()
{
	SpawnManager->RespawnMonster(ObjectIndex);
}
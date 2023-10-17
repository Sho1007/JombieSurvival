// Fill out your copyright notice in the Description page of Project Settings.


#include "../Enemy/ZombieBase.h"

#include <Engine/DamageEvents.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>

#include "../../Weapon/ProjectileBase.h"
#include "../../Item/ItemBase.h"
#include "../../SpawnManager.h"
#include "../Player/PlayerBase.h"
#include "../../Weapon/ShotGunHitBox.h"

AZombieBase::AZombieBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;


	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	CapsuleComponent->SetCollisionProfileName(TEXT("BlockOnlyCapsule"));

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	SkeletalMeshComponent->SetCollisionProfileName(TEXT("TraceOnlyMesh"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AZombieBase::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Tick"));
	Super::Tick(DeltaTime);

	if (Player) MoveDirection = Player->GetActorLocation() - GetActorLocation();
	if (MoveDirection.Length() >= RespawnDistance) Respawn();

	if (!bIsAttacking)
	{
		Move(DeltaTime);

		if (bIsAttackable) Attack();
	}
}

void AZombieBase::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Attack Called"));

	if (bIsAttacking == false)
	{
		bIsAttacking = true;

		StopMoving();

		AudioComponent->SetPaused(true);
		PlayAnimMontage(AttackMontage);
	}
}

void AZombieBase::EndAttack()
{
	if (bIsActived)
	{
		bIsAttacking = false;
		AudioComponent->SetPaused(false);
	}
}

void AZombieBase::EndReact()
{
	if (bIsActived) AudioComponent->SetPaused(false);
}

void AZombieBase::CheckHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CheckHit Called"));

	FHitResult OutHit;
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * AttackRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Pawn, Params))
	{
		//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CheckHit) Hitted Actor : %s"), *OutHit.GetActor()->GetName());
		OutHit.GetActor()->TakeDamage(AttackDamage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CheckHit) Check"));
		SetActorRotation(MoveDirection.Rotation());
	}
}

void AZombieBase::StartMoving()
{
	
}

void AZombieBase::StopMoving()
{
	
}

float AZombieBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::TakeDamage) %f"), DamageAmount);

	if (bIsActived == false) return 0.0f;

	AudioComponent->SetPaused(true);
	if (bIsKnockBackable)
	{
		bIsAttackable = false;
		bIsAttacking = false;
		StopMoving();
		StopAnimMontage();
		if (HittedMontage) PlayAnimMontage(HittedMontage);
		if (AProjectileBase* Projectile = Cast<AProjectileBase>(DamageCauser)) AddActorWorldOffset(GetActorForwardVector() * -Projectile->GetKnockbackPower(), false, nullptr, ETeleportType::ResetPhysics);
		else if (AShotGunHitBox* ShotGunHitBox = Cast<AShotGunHitBox>(DamageCauser)) AddActorWorldOffset(GetActorForwardVector() * -ShotGunHitBox->GetKnockBackPower(), false, nullptr, ETeleportType::ResetPhysics);
	}

	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		DropItem();

		this->Disactive();
	}

	return 0.0f;
}

void AZombieBase::DropItem()
{
	SpawnManager->SpawnMoney(GetActorLocation(), 30);
	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		//GetWorld()->SpawnActor<AItemBase>(ItemArray[i], GetActorLocation(), FRotator::ZeroRotator);
	}
}

void AZombieBase::Move(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Move) Called"));
	if (MoveDirection.Length() >= AttackRange)
	{
		bIsAttackable = false;
		bIsMoving = true;
		
		// Todo
		//GetCharacterMovement()->Velocity = MoveDirection;

		// Rotate
		SetActorRotation(FMath::Lerp(GetActorRotation(), MoveDirection.Rotation(), 0.5f));

		//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Tick) Check"));

		FHitResult OutHit;
		FVector Start = GetActorLocation() + (GetActorForwardVector() * 10.0f);
		FVector End = Start + (GetActorForwardVector() * 100.0f);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		MoveDirection = GetActorForwardVector();
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params))
		{
			if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End + (GetActorRightVector() * 50.0f), ECC_Visibility, Params))
			{
				MoveDirection = -GetActorRightVector();
			}
			else
			{
				MoveDirection = GetActorRightVector();
			}
		}

		MoveDirection.Normalize();
		//DrawDebugLine(GetWorld(), Start, Start + (MoveDirection * 100.0f), FColor::Yellow, false, 2.0f);
		AddActorWorldOffset(MoveDirection * Speed * DeltaTime, true);	
	}
	else
	{
		bIsAttackable = true;
		bIsMoving = false;
	}
}

void AZombieBase::Disactive()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Disactive"));
	bIsActived = false;
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

	AudioComponent->SetPaused(true);

	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
	SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AZombieBase::Active()
{
	//UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Active"));
	bIsActived = true;
	SetActorTickEnabled(true);
	StopAnimMontage();
	bIsAttackable = false;
	bIsAttacking = false;

	
	
	AudioComponent->Play(FMath::RandRange(0.0f, AmbianceSound->Duration));	
	AudioComponent->SetPaused(false);
	
	CapsuleComponent->SetCollisionProfileName(TEXT("BlockOnlyCapsule"));

	SkeletalMeshComponent->SetCollisionProfileName(TEXT("TraceOnlyMesh"));

	Health = MaxHealth;

	StartMoving();

	SetActorHiddenInGame(false);

	if (AmbianceSound)
	{
		AudioComponent->SetSound(AmbianceSound);
		AudioComponent->Play();
	}
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

void AZombieBase::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	if (AnimMontage && AnimInstance)
	{
		float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

		if (Duration > 0.f)
		{
			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}
		}
	}
}

void AZombieBase::StopAnimMontage(UAnimMontage* AnimMontage)
{
	UAnimInstance* AnimInstance = (SkeletalMeshComponent) ? SkeletalMeshComponent->GetAnimInstance() : nullptr;
	UAnimMontage* MontageToStop = (AnimMontage) ? AnimMontage : AnimInstance->GetCurrentActiveMontage();
	bool bShouldStopMontage = AnimInstance && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

	if (bShouldStopMontage)
	{
		AnimInstance->Montage_Stop(MontageToStop->BlendOut.GetBlendTime(), MontageToStop);
	}
}
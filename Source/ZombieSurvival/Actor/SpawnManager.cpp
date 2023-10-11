// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Character/Enemy/ZombieBase.h"
#include "Character/Enemy/BossBase.h"
#include "Character/Player/PlayerBase.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerBase>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Player == nullptr) UE_LOG(LogTemp, Error, TEXT("ASpawnManager::BeginPlay) Player is nullptr"));

	PrepareMonster();

	CurrentMonsterSpawnTime = MonsterSpawnTime;
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentMonsterSpawnTime += DeltaTime;
	if (CurrentMonsterSpawnTime >= MonsterSpawnTime)
	{
		CurrentMonsterSpawnTime = 0;
		SpawnMonster();
	}
	
	CurrentBossSpawnTime+= DeltaTime;
	if (CurrentBossSpawnTime >= BossSpawnTime)
	{
		CurrentBossSpawnTime = 0;
		SpawnBoss();
	}
}

void ASpawnManager::RespawnMonster(int ObjectIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::RespawnMonster) Respawn Index : %d"), ObjectIndex);
	ZombieArray[ObjectIndex]->SetActorLocation(GetSpawnLocation());
}

void ASpawnManager::SpawnMonster()
{
	for (int i = 0; i < ZombieArray.Num(); ++i)
	{
		if (ZombieArray[i]->IsActive() == false)
		{
			ZombieArray[i]->SetActorLocation(GetSpawnLocation());
			ZombieArray[i]->Active();
			CurrentSpawnedCount++;
			break;
		}
	}
}

void ASpawnManager::SpawnBoss()
{
	if (BossClass == nullptr) return;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABossBase* Boss = GetWorld()->SpawnActor<ABossBase>(BossClass, GetSpawnLocation(), FRotator::ZeroRotator, Params);
	Boss->Active();
}

FVector ASpawnManager::GetSpawnLocation()
{
	FVector SpawnDirection;

	FVector MoveDirection = Player->GetCharacterMovement()->GetLastUpdateVelocity();
	
	if (MoveDirection == FVector::Zero())
	{
		SpawnDirection = Player->GetActorForwardVector().RotateAngleAxis(FMath::FRandRange(0.0f, 359.0f), FVector(0, 0, 1));
	}
	else
	{
		MoveDirection.Normalize();
		SpawnDirection = MoveDirection;
		SpawnDirection = SpawnDirection.RotateAngleAxis(FMath::FRandRange(-90.0f, 90.0f), FVector(0, 0, 1));
	}
	//DrawDebugLine(GetWorld(), Player->GetActorLocation(), Player->GetActorLocation() + SpawnDirection * FMath::FRandRange(MonsterSpawnDistance - 100.0f, MonsterSpawnDistance + 100.0f), FColor::Cyan, false, 5);

	return Player->GetActorLocation() + SpawnDirection * FMath::FRandRange(MonsterSpawnDistance - 100.0f, MonsterSpawnDistance + 100.0f);
}

void ASpawnManager::PrepareMonster()
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < ObjectPoolingCount; ++i)
	{
		AZombieBase* Zombie = GetWorld()->SpawnActor<AZombieBase>(ZombieClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		Zombie->Init(Player, this, i);
		Zombie->Disactive();
		//Zombie->OnDied.AddDynamic();
		ZombieArray.Add(Zombie);
	}
}
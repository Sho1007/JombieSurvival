// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Character/Enemy/ZombieBase.h"
#include "Character/Enemy/BossBase.h"
#include "Character/Player/PlayerBase.h"
#include "Weapon/ProjectileBase.h"
#include "../ZombieSurvivalGameState.h"
#include "../Actor/Item/MoneyBase.h"

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
	PrepareProjectile();
	PrepareMoney();

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

void ASpawnManager::UpdateStageData(FStageData& NewStageData)
{
	BossSpawnTime = NewStageData.BossSpawnTime;
	MaxMonsterCount = NewStageData.MaxMonsterCount >= ZombieArray.Num()  ? NewStageData.MaxMonsterCount : ZombieArray.Num();
	MonsterSpawnTime = NewStageData.MonsterSpawnTime;
}

void ASpawnManager::RespawnMonster(int ObjectIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::RespawnMonster) Respawn Index : %d"), ObjectIndex);
	ZombieArray[ObjectIndex]->SetActorLocation(GetSpawnLocation());
}

void ASpawnManager::SpawnMonster()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::SpawnMonster) Called"));
	for (int i = 0; i < MaxMonsterCount; ++i)
	{
		if (ZombieArray[i]->IsActive() == false)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::SpawnMonster) Check"));
			ZombieArray[i]->SetActorLocation(GetSpawnLocation());
			ZombieArray[i]->Active();
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

void ASpawnManager::SpawnProjectile(FVector ProjectileLocaiton, FRotator ProjectileRotation, FName ProjectileName)
{
	// Find Proejctile Information

	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		if (ProjectileArray[i]->IsActive() == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::SpawnProjectile) SpawnIndex : %d"), i);
			ProjectileArray[i]->SetActorLocationAndRotation(ProjectileLocaiton, ProjectileRotation);
			// Todo : Apply Projectile Property From Projectile Information
			ProjectileArray[i]->Active();
			break;
		}
	}
}

void ASpawnManager::SpawnMoney(FVector MoneyLocation, int NewExpAMount)
{
	if (ActivedMoneyCount == MoneyArray.Num())
	{
		int Index = FMath::RandRange(0, MoneyArray.Num() - 1);
		MoneyArray[Index]->AddExpAmount(NewExpAMount);
		MoneyArray[Index]->SetActorLocation(MoneyLocation);
		return;
	}
	for (int i = 0; i < MoneyArray.Num(); ++i)
	{
		if (MoneyArray[i] && MoneyArray[i]->IsActive() == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::SpawnMoney) SpawnIndex : %d"), i);
			MoneyArray[i]->SetActorLocation(MoneyLocation);
			MoneyArray[i]->SetExpAmount(NewExpAMount);
			// Todo : Apply Projectile Property From Projectile Information
			MoneyArray[i]->Activate();
			ActivedMoneyCount++;
			break;
		}
	}
}

void ASpawnManager::ReduceActivedMoneyCount()
{
	ActivedMoneyCount = ActivedMoneyCount - 1 >= 0 ? ActivedMoneyCount - 1 : 0;
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
	for (int i = 0; i < ZombiePoolingCount; ++i)
	{
		AZombieBase* Zombie = GetWorld()->SpawnActor<AZombieBase>(ZombieClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		Zombie->Init(Player, this, i);
		Zombie->Disactive();
		ZombieArray.Add(Zombie);
	}
}

void ASpawnManager::PrepareProjectile()
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < ProjectilePoolingCount; ++i)
	{
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		Projectile->Init(this, i);
		Projectile->Disactive();
		ProjectileArray.Add(Projectile);
	}
}

void ASpawnManager::PrepareMoney()
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < MoneyPoolingCount; ++i)
	{
		AMoneyBase* Money = GetWorld()->SpawnActor<AMoneyBase>(MoneyClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		Money->Init(this);
		Money->Deactivate();
		MoneyArray.Add(Money);
	}
}
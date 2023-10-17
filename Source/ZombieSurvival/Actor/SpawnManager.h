// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class AZombieBase;
class AProjectileBase;
class ABossBase;
class APlayerBase;
class AMoneyBase;

struct FStageData;
UCLASS()
class ZOMBIESURVIVAL_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateStageData(FStageData& NewStageData);

	void RespawnMonster(int ObjectIndex);
	void SpawnProjectile(FVector ProjectileLocaiton, FRotator ProjectileRotation, FName ProjectileName);
	void SpawnMoney(FVector MoneyLocation, int NewExpAMount);

	void ReduceActivedMoneyCount();
private:
	void SpawnMonster();
	void SpawnBoss();
	
	FVector GetSpawnLocation();

	void PrepareMonster();
	void PrepareProjectile();
	void PrepareMoney();

private:
	APlayerBase* Player;
	// Monster ObjectPooling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	int MaxMonsterCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	int32 ZombiePoolingCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	TArray<AZombieBase*> ZombieArray;
	
	// Projectile ObjectPooling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Spawn", Meta = (AllowPrivateAccess))
	int32 ProjectilePoolingCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Spawn", Meta = (AllowPrivateAccess))
	TArray<AProjectileBase*> ProjectileArray;
	
	// Money ObjectPooling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money Spawn", Meta = (AllowPrivateAccess))
	int32 MoneyPoolingCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money Spawn", Meta = (AllowPrivateAccess))
	int32 ActivedMoneyCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money Spawn", Meta = (AllowPrivateAccess))
	TArray<AMoneyBase*> MoneyArray;

	// Spawn Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	float MonsterSpawnTime;
	float CurrentMonsterSpawnTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	float BossSpawnTime;
	float CurrentBossSpawnTime;

	// Spawn Distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	float MonsterSpawnDistance;

	// class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<AActor> ZombieClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<ABossBase> BossClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<AMoneyBase> MoneyClass;
};
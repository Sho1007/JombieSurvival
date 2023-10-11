// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class AZombieBase;
class ABossBase;
class APlayerBase;
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

	void RespawnMonster(int ObjectIndex);

private:
	void SpawnMonster();
	void SpawnBoss();

	FVector GetSpawnLocation();

	void PrepareMonster();

private:
	// Monster Spawn
	APlayerBase* Player;

	// ObjectPooling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	int32 ObjectPoolingCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	int32 CurrentSpawnedCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	TArray<AZombieBase*> ZombieArray;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<AZombieBase> ZombieClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<ABossBase> BossClass;
};
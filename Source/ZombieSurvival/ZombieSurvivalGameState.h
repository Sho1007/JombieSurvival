// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ZombieSurvivalGameState.generated.h"

DECLARE_DELEGATE_OneParam(FDele_Single_One_Float, float);

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStageData
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StartTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MonsterSpawnTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BossSpawnTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxMonsterCount;

	// Todo : Specify Spawn Monster Type
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> MonsterName;
};
class ASpawnManager;
UCLASS()
class ZOMBIESURVIVAL_API AZombieSurvivalGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AZombieSurvivalGameState();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	void MoveToNextStage();
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (AllowPrivateAccess))
	ASpawnManager* SpawnManager;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (AllowPrivateAccess))
	int StageLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (AllowPrivateAccess))
	float GameTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TArray<FStageData> StageDataArray;

public:
	// Delegate
	FDele_Single_One_Float OnGameTimeUpdated;
};
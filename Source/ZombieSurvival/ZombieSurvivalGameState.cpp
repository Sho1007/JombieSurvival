// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSurvivalGameState.h"

#include <EngineUtils.h>

#include "Actor/SpawnManager.h"

AZombieSurvivalGameState::AZombieSurvivalGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombieSurvivalGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTime += DeltaTime;
	OnGameTimeUpdated.ExecuteIfBound(GameTime);

	if (StageLevel < StageDataArray.Num() - 1)
	{
		if (GameTime >= StageDataArray[StageLevel + 1].StartTime)
		{
			StageLevel++;
			MoveToNextStage();
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("AZombieSurvivalGameState::Tick) GameTime : %f"), GameTime);
}

void AZombieSurvivalGameState::BeginPlay()
{
	Super::BeginPlay();

	TActorIterator<AActor> It(GetWorld(), ASpawnManager::StaticClass());
	if (ASpawnManager* NewSpawnManager = Cast<ASpawnManager>(*It))
	{
		SpawnManager = NewSpawnManager;
		UE_LOG(LogTemp, Warning, TEXT("AZombieSurvivalGameState::BeginPlay) SpawnManaer : %s"), *SpawnManager->GetName());
	}

	MoveToNextStage();
}

void AZombieSurvivalGameState::MoveToNextStage()
{
	// Todo : Notify Stage Change by use Widget
	UE_LOG(LogTemp, Warning, TEXT("AZombieSurvivalGameState::MoveToNextStage) %d"), StageLevel);
	SpawnManager->UpdateStageData(StageDataArray[StageLevel]);
}
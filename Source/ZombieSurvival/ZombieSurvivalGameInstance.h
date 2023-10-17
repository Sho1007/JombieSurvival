// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Engine/DataTable.h>
#include "ZombieSurvivalGameInstance.generated.h"

/**
 * 
 */
class UTexture2D;
USTRUCT(BlueprintType)
struct FStatData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* StatImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText StatName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<float> StatArray;
};

UCLASS()
class ZOMBIESURVIVAL_API UZombieSurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FStatData* FindStatData(FName Row) const;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	UDataTable* StatDataTable;
};
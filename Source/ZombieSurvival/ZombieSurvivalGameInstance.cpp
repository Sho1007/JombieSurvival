// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSurvivalGameInstance.h"

FStatData* UZombieSurvivalGameInstance::FindStatData(FName Row) const
{

    return StatDataTable->FindRow<FStatData>(Row, "");
}
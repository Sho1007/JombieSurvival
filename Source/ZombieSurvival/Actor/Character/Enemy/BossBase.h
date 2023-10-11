// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Enemy/ZombieBase.h"
#include "BossBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESURVIVAL_API ABossBase : public AZombieBase
{
	GENERATED_BODY()
	
protected:
	virtual void Respawn() override;
};
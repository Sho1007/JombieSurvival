// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "GunBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESURVIVAL_API AGunBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	void AddBullet(int32 NewBulletAmount);
	
protected:
	virtual void Attack() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	int32 BulletAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	float TraceRadius;
};
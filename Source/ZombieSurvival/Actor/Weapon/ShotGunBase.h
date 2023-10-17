// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/GunBase.h"
#include "ShotGunBase.generated.h"

/**
 * 
 */
class AShotGunHitBox;
UCLASS()
class ZOMBIESURVIVAL_API AShotGunBase : public AGunBase
{
	GENERATED_BODY()
	
	friend class AShotGunHitBox;
public:
	virtual void BeginPlay() override;
protected:
	virtual void FireBullet() override;
private:
	void ApplyDamage(AActor* TargetActor);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotGun", Meta = (AllowPrivateAccess))
	AShotGunHitBox* ShotGunHitBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotGun", Meta = (AllowPrivateAccess))
	TSubclassOf<AShotGunHitBox> ShotGunHitBoxClass;
};
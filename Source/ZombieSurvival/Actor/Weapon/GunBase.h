// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "GunBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGunType : uint8
{
	NONE,
	RIFLE,
	SHOTGUN,

};

class USkeletalMeshComponent;
class UArrowComponent;
class ASpawnManager;
class APlayerBase;
UCLASS()
class ZOMBIESURVIVAL_API AGunBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AGunBase();

	void AddBullet(int32 NewBulletAmount);

	virtual void BeginPlay() override;

	void SetPlayer(APlayerBase* NewPlayer);

	void SetDamage(float NewDamage);

	EGunType GetGunType() const;
protected:
	virtual void Attack() override;
	virtual void FireBullet();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	EGunType GunType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	USoundBase* GunFireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	TSubclassOf<AActor> GunFireClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	APlayerBase* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	ASpawnManager* SpawnManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	int32 BulletAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	float TraceRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", Meta = (AllowPrivateAccess))
	UArrowComponent* MuzzleArrowComponent;
};
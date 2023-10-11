// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "ZombieBase.generated.h"

DECLARE_DELEGATE(FDele_Single);

/**
 * 
 */
class AItemBase;
class UAnimMontage;
class ASpawnManager;
class APlayerBase;
UCLASS()
class ZOMBIESURVIVAL_API AZombieBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	AZombieBase(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Attack();
	
	UFUNCTION(BlueprintCallable)
	void CheckHit();

	UFUNCTION(BlueprintCallable)
	void StartMoving();
	UFUNCTION(BlueprintCallable)
	void StopMoving();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void DropItem();

	// Object Pooling
	UFUNCTION(CallInEditor)
	void Disactive();
	UFUNCTION(CallInEditor)
	void Active();

	bool IsActive() const;

	void Init(APlayerBase* NewPlayer, ASpawnManager* NewSpawnManager, int NewObjectIndex);

	virtual void Respawn();

	FDele_Single OnDied;
protected:
	// Object Pooling
	ASpawnManager* SpawnManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	int32 ObjectIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	bool bIsActived;

	// Enemy FSM
	APlayerBase* Player;

	
	// Item Loot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<AItemBase>> ItemArray;

	// Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	bool bIsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	bool bIsAttackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	float AttackDamage;

	// Hitted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	UAnimMontage* HittedMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	bool bIsKnockBackable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie", Meta = (AllowPrivateAccess))
	float MaxHealth;
	float Health;
};
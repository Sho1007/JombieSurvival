// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "PlayerBase.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FDele_Single_One_Float, float);
DECLARE_DELEGATE_TwoParams(FDele_Single_Two_Float_Float, float, float);

class USphereComponent;
class AGunBase;
class UWidgetComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
UCLASS()
class ZOMBIESURVIVAL_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerBase();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void AddExp(int32 NewExp);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddBullet(int32 NewBulletAmount);
	void AddBullet_Implementation(int32 NewBulletAmount);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Die() override;

	void PlayFireMontage();

	// Level Up Stat
	void LevelUp(FText StatName);
public:
	// Getter / Setter

	float GetCurrentExp() const;
	float GetMaxExp() const;

	int GetDamageLevel() const;
	int GetArmorLevel() const;
	int GetSpeedLevel() const;
	int GetHealthLevel() const;
private:
	void Move(const FInputActionValue& Value);

	// Setter (For Delegate)
	void SetCurrentHealth(float NewCurrentHealth);
	void SetMaxHealth(float NewMaxHealth);

	void SetCurrentExp(float NewCurrentExp);
	void SetMaxExp(float NewMaxExp);

	// Setter (Status)
	void SetDamageStat();
	void SetArmorStat();
	void SetSpeedStat();
	void SetHealthStat();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	UWidgetComponent* HPBarWidgetComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	bool bIsDead;

	// Status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	int DamageLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	int ArmorLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	int SpeedLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess))
	int HealthLevel;

	// Level Up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", Meta = (AllowPrivateAccess))
	int CurrentExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", Meta = (AllowPrivateAccess))
	int MaxExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", Meta = (AllowPrivateAccess))
	int CurrentLevel;

	// Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	AGunBase* Gun;								
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	TSubclassOf<AGunBase> GunClass;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	float MinRotateDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	UInputAction* InputAction_Move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	UAnimMontage* RifleFireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	UAnimMontage* ShotGunFireMontage;
public:
	// Delegate
	FDele_Single_One_Float OnHPUpdated;
	FDele_Single_Two_Float_Float OnExpUpdated;
};
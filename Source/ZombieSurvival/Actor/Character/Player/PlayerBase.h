// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "PlayerBase.generated.h"

/**
 * 
 */

class USphereComponent;
class AGunBase;
UCLASS()
class ZOMBIESURVIVAL_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void EarnMoeny(int32 NewMoneyAmount);
	void EarnMoeny_Implementation(int32 NewMoneyAmount);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddBullet(int32 NewBulletAmount);
	void AddBullet_Implementation(int32 NewBulletAmount);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnVisibleAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	USphereComponent* VisibleArea;				
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	int BulletAmount;							
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	int MoneyAmount;							
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	AGunBase* Gun;								
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess))
	TSubclassOf<AGunBase> GunClass;
};
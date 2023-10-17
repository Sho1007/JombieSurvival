// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "Knife.generated.h"

/**
 * 
 */
class UStaticMeshComponent;
class UCapsuleComponent;
class APlayerBase;
UCLASS()
class ZOMBIESURVIVAL_API AKnife : public AWeaponBase
{
	GENERATED_BODY()
	
	AKnife();

	virtual void Attack() override;

	virtual void Tick(float DeltaTime) override;

	void Stab(float DeltaTime);
	void Return(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void InitPlayer(ACharacter* NewPlayer);

	UFUNCTION()
	void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	ACharacter* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	float StabSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	float ReturnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	UCapsuleComponent* HitBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	bool bIsAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knife", Meta = (AllowPrivateAccess))
	bool bIsReturn;
};
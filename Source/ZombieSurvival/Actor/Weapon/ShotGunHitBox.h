// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShotGunHitBox.generated.h"

class UStaticMeshComponent;
class AShotGunBase;
UCLASS()
class ZOMBIESURVIVAL_API AShotGunHitBox : public AActor
{
	GENERATED_BODY()
	
friend class AShotGunBase;
public:	
	// Sets default values for this actor's properties
	AShotGunHitBox();

	virtual void BeginPlay() override;
	void Init(AShotGunBase* NewShotGun);

public:
	// Getter
	AShotGunBase* GetShotGun() const;
	float GetKnockBackPower() const;
private:
	void Fire();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotGunHitBox", Meta = (AllowPrivateAccess))
	AShotGunBase* ShotGun;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotGunHitBox", Meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;
};
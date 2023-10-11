// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemBase.h"
#include "BulletBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESURVIVAL_API ABulletBase : public AItemBase
{
	GENERATED_BODY()
	
	virtual void Interact(AActor* InteractActor) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	int BulletAmount;
};
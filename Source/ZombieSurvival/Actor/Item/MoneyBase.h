// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemBase.h"
#include "MoneyBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESURVIVAL_API AMoneyBase : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AActor* InteractActor) override;

	virtual void Deactivate() override;
	
	void SetExpAmount(int32 NewExpAmount);
	void AddExpAmount(int32 NewExpAmount);
	int GetExpAmount() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	int32 ExpAmount;
};
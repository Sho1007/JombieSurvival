// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/MoneyBase.h"

#include "../Character/Player/PlayerBase.h"
#include "../SpawnManager.h"

void AMoneyBase::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);
	
	if (APlayerBase* Player = Cast<APlayerBase>(InteractActor))
	{
		Player->AddExp(ExpAmount);
		this->Deactivate();
	}
}

void AMoneyBase::Deactivate()
{
	Super::Deactivate();

	SpawnManager->ReduceActivedMoneyCount();
}

void AMoneyBase::SetExpAmount(int32 NewExpAmount)
{
	ExpAmount = NewExpAmount;
}

void AMoneyBase::AddExpAmount(int32 NewExpAmount)
{
	ExpAmount += NewExpAmount;

	// Todo : Update Static Mesh depend on ExpAmount;
}

int AMoneyBase::GetExpAmount() const
{
	return ExpAmount;
}
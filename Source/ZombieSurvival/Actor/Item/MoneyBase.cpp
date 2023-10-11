// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/MoneyBase.h"

#include "../Character/Player/PlayerBase.h"

void AMoneyBase::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);
	
	if (APlayerBase* Player = Cast<APlayerBase>(InteractActor))
	{
		Player->EarnMoeny(MoneyAmount);
		this->Destroy();
	}
}
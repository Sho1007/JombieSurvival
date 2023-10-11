// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/BulletBase.h"

#include "../Character/Player/PlayerBase.h"

void ABulletBase::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);

	if (APlayerBase* Player = Cast<APlayerBase>(InteractActor))
	{
		Player->AddBullet(BulletAmount);
		Destroy();
	}
}
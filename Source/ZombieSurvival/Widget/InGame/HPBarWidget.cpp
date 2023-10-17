// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGame/HPBarWidget.h"

#include <Components/ProgressBar.h>

#include "../../Actor/Character/Player/PlayerBase.h"

void UHPBarWidget::InitPlayer(APlayerBase* NewPlayer)
{
	NewPlayer->OnHPUpdated.BindUObject(this, &UHPBarWidget::UpdateHealth);
}

void UHPBarWidget::UpdateHealth(float HealthPercent)
{
	//UE_LOG(LogTemp, Warning, TEXT("UHPBarWidget::UpdateHealth) %f"), HealthPercent);
	HPProgressBar->SetPercent(HealthPercent);
}
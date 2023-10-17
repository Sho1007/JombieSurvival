// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerController/InGamePlayerController.h"
#include "../../Widget/InGame/GameOverWidget.h"
#include "../../Widget/InGame/LevelUpWidget.h"

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);

	if (LevelUpWidgetClass)
	{
		LevelUpWidget = CreateWidget<ULevelUpWidget>(this, LevelUpWidgetClass);
		if (LevelUpWidget)
		{
			LevelUpWidget->InitWidget(GetCharacter());
			LevelUpWidget->AddToViewport();

		}
	}
}

void AInGamePlayerController::ShowGameOverWidget()
{
	GameOverWidget = CreateWidget<UGameOverWidget>(this, GameOverWidgetClass, TEXT("GameOverWidget"));
	check(GameOverWidget);
	GameOverWidget->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void AInGamePlayerController::LevelUp(int CurrentLevel)
{
	SetPause(true);
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
	LevelUpWidget->LevelUp();
}

void AInGamePlayerController::EndLevelUp()
{
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
	LevelUpWidget->EndLevelUp();
}
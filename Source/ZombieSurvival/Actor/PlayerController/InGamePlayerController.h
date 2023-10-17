// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
class UGameOverWidget;
class ULevelUpWidget;
UCLASS()
class ZOMBIESURVIVAL_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void ShowGameOverWidget();

	void LevelUp(int CurrentLevel);
	void EndLevelUp();
private:
	UPROPERTY(EditAnywhere, Category = "InGamePlayerController", Meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameOverWidget> GameOverWidgetClass;
	UGameOverWidget* GameOverWidget;
	
	UPROPERTY(EditAnywhere, Category = "InGamePlayerController", Meta = (AllowPrivateAccess = true))
	TSubclassOf<ULevelUpWidget> LevelUpWidgetClass;
	ULevelUpWidget* LevelUpWidget;
};
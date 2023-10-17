// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

/**
 * 
 */
class APlayerBase;
class UProgressBar;
UCLASS()
class ZOMBIESURVIVAL_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitPlayer(APlayerBase* NewPlayer);

private:
	UFUNCTION()
	void UpdateHealth(float HealthPercent);

private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UProgressBar* HPProgressBar;
};
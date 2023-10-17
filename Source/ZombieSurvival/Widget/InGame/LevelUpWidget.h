// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;
class UVerticalBox;
class ULevelUpSlotWidget;
UCLASS()
class ZOMBIESURVIVAL_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(ACharacter* NewPlayer);

	void LevelUp();
	void EndLevelUp();

	void BindGameTime();
private:
	UFUNCTION()
	void UpdateGameTime(float NewGameTime);

	UFUNCTION()
	void UpdateExp(float CurrentExp, float MaxExp);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess, BindWidget))
	UProgressBar* ProgressBar_ExpBar;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_CurrentExp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_MaxExp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess, BindWidget))
	UVerticalBox* VB_LevelUpPannel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess, BindWidget))
	UVerticalBox* VB_StatList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_GameTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUpWidget", Meta = (AllowPrivateAccess))
	TSubclassOf<ULevelUpSlotWidget> LevelUpSlotWidgetClass;
};
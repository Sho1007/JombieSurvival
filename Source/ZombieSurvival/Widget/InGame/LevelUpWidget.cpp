// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGame/LevelUpWidget.h"

#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>
#include <Components/VerticalBox.h>

#include "../../Actor/Character/Player/PlayerBase.h"
#include "../../ZombieSurvivalGameInstance.h"
#include "../../ZombieSurvivalGameState.h"
#include "LevelUpSlotWidget.h"

void ULevelUpWidget::InitWidget(ACharacter* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("ULevelUpWidget::InitWidget"));
	if (APlayerBase* Player = Cast<APlayerBase>(NewPlayer))
	{
		float CurrentExp = Player->GetCurrentExp();
		float MaxExp = Player->GetMaxExp();
		ProgressBar_ExpBar->SetPercent(CurrentExp / MaxExp);
		Txt_CurrentExp->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int)CurrentExp)));
		Txt_MaxExp->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int)MaxExp)));
		Player->OnExpUpdated.BindUFunction(this, TEXT("UpdateExp"));
	}

	BindGameTime();
}

void ULevelUpWidget::LevelUp()
{
	if (LevelUpSlotWidgetClass == nullptr) return;
	if (UZombieSurvivalGameInstance* Instance = GetGameInstance<UZombieSurvivalGameInstance>())
	{
		VB_StatList->ClearChildren();
		if (APlayerBase* Player = GetOwningPlayerPawn<APlayerBase>())
		{
			if (FStatData* SlotData = Instance->FindStatData("Damage"))
			{
				if (Player->GetDamageLevel() < SlotData->StatArray.Num() - 1)
				{
					ULevelUpSlotWidget* SlotWidget = CreateWidget<ULevelUpSlotWidget>(GetOwningPlayer(), LevelUpSlotWidgetClass);
					SlotWidget->InitWidget(SlotData->StatImage, SlotData->StatName);
					VB_StatList->AddChildToVerticalBox(SlotWidget);
					SlotWidget->SetPadding(FMargin(10.0f));
				}
			}
			
			if (FStatData* SlotData = Instance->FindStatData("Armor"))
			{
				if (Player->GetArmorLevel() < SlotData->StatArray.Num() - 1)
				{
					ULevelUpSlotWidget* SlotWidget = CreateWidget<ULevelUpSlotWidget>(GetOwningPlayer(), LevelUpSlotWidgetClass);
					SlotWidget->InitWidget(SlotData->StatImage, SlotData->StatName);
					VB_StatList->AddChildToVerticalBox(SlotWidget);
					SlotWidget->SetPadding(FMargin(10.0f));
				}
			}
			
			if (FStatData* SlotData = Instance->FindStatData("Speed"))
			{
				if (Player->GetSpeedLevel() < SlotData->StatArray.Num() - 1)
				{
					ULevelUpSlotWidget* SlotWidget = CreateWidget<ULevelUpSlotWidget>(GetOwningPlayer(), LevelUpSlotWidgetClass);
					SlotWidget->InitWidget(SlotData->StatImage, SlotData->StatName);
					VB_StatList->AddChildToVerticalBox(SlotWidget);
					SlotWidget->SetPadding(FMargin(10.0f));
				}
			}

			if (FStatData* SlotData = Instance->FindStatData("Health"))
			{
				if (Player->GetHealthLevel() < SlotData->StatArray.Num() - 1)
				{
					ULevelUpSlotWidget* SlotWidget = CreateWidget<ULevelUpSlotWidget>(GetOwningPlayer(), LevelUpSlotWidgetClass);
					SlotWidget->InitWidget(SlotData->StatImage, SlotData->StatName);
					VB_StatList->AddChildToVerticalBox(SlotWidget);
					SlotWidget->SetPadding(FMargin(10.0f));
				}
			}

			VB_LevelUpPannel->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ULevelUpWidget::EndLevelUp()
{
	VB_LevelUpPannel->SetVisibility(ESlateVisibility::Collapsed);
}

void ULevelUpWidget::BindGameTime()
{
	if (AZombieSurvivalGameState* GS = GetWorld()->GetGameState<AZombieSurvivalGameState>())
	{
		GS->OnGameTimeUpdated.BindUFunction(this, TEXT("UpdateGameTime"));
	}
}

void ULevelUpWidget::UpdateGameTime(float NewGameTime)
{
	Txt_GameTime->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), NewGameTime)));
}

void ULevelUpWidget::UpdateExp(float CurrentExp, float MaxExp)
{
	Txt_CurrentExp->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int)CurrentExp)));
	Txt_MaxExp->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int)MaxExp)));

	ProgressBar_ExpBar->SetPercent(CurrentExp / MaxExp);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGame/LevelUpSlotWidget.h"

#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>

#include "../../Actor/Character/Player/PlayerBase.h"

bool ULevelUpSlotWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	Btn_SlotButton->OnClicked.AddDynamic(this, &ULevelUpSlotWidget::OnSlotButtonClicked);

	return true;
}

void ULevelUpSlotWidget::InitWidget(UTexture2D* NewSlotImage, FText NewSlotText)
{
	Img_SlotImage->SetBrushFromTexture(NewSlotImage);
	Txt_SlotText->SetText(NewSlotText);
}

void ULevelUpSlotWidget::OnSlotButtonClicked()
{
	if (APlayerBase* Player = Cast<APlayerBase>(GetOwningPlayerPawn()))
	{
		Player->LevelUp(Txt_SlotText->GetText());
	}
}
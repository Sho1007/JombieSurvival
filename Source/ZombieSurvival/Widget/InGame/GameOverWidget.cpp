// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGame/GameOverWidget.h"

#include <Components/Button.h>

bool UGameOverWidget::Initialize()
{
	bool Result = Super::Initialize();

	Btn_Resume->OnClicked.AddDynamic(this, &UGameOverWidget::ResumeButtonOnClicked);
	return Result;
}

void UGameOverWidget::ResumeButtonOnClicked()
{
	//GetOwningPlayer()->SetPause(false);
	GetOwningPlayer()->ClientTravel(TravelURL, TRAVEL_Absolute);
}
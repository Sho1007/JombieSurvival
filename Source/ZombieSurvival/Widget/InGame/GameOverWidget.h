// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class ZOMBIESURVIVAL_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
private:
	UFUNCTION()
	void ResumeButtonOnClicked();

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	FString TravelURL;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UButton* Btn_Resume;
};

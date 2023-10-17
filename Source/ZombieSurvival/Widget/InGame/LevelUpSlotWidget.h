// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpSlotWidget.generated.h"

/**
 * 
 */
class UButton;
class UImage;
class UTextBlock;
UCLASS()
class ZOMBIESURVIVAL_API ULevelUpSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual bool Initialize() override;

public:
	void InitWidget(UTexture2D* NewSlotImage, FText NewSlotText);
private:
	UFUNCTION()
	void OnSlotButtonClicked();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess, BindWidget))
	UButton* Btn_SlotButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess, BindWidget))
	UImage* Img_SlotImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* Txt_SlotText;
};

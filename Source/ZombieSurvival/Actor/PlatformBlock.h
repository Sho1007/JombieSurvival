// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformBlock.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UNavModifierComponent;
UCLASS()
class ZOMBIESURVIVAL_API APlatformBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	UNavModifierComponent* NavModifierComponent;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../../Interface/InteractInterface.h"

#include "ItemBase.generated.h"

class UStaticMeshComponent;
class ASpawnManager;
UCLASS()
class ZOMBIESURVIVAL_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	// Inherited via IInteractInterface
	virtual void Interact(AActor* InteractActor) override;

	void Init(ASpawnManager* NewSpawnManager);

	virtual void Activate();
	virtual void Deactivate();

	bool IsActive() const;
protected:
	// Object Pooling
	bool bIsActived;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	ASpawnManager* SpawnManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;
};
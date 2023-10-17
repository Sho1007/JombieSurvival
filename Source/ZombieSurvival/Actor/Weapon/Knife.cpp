// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Knife.h"

#include <GameFramework/Character.h>
#include <Components/StaticMeshComponent.h>
#include <Components/CapsuleComponent.h>

AKnife::AKnife()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	HitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(StaticMeshComponent);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AKnife::OnHitBoxBeginOverlap);
}

void AKnife::Attack()
{
	if (bIsAttack || bIsReturn) return;
	bIsAttack = true;
}

void AKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttack)
	{
		Stab(DeltaTime);
	}
	else if (bIsReturn)
	{
		Return(DeltaTime);
	}
}

void AKnife::Stab(float DeltaTime)
{
	
	//UE_LOG(LogTemp, Warning, TEXT("AKnife::Stab"));
	StaticMeshComponent->AddWorldOffset(GetActorForwardVector() * DeltaTime * StabSpeed, true);
	if (StaticMeshComponent->GetRelativeLocation().Length() >= 200.0f)
	{
		bIsAttack = false;
		bIsReturn = true;
	}
}

void AKnife::Return(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("AKnife::Return"));
	StaticMeshComponent->AddWorldOffset(GetActorForwardVector() * DeltaTime * -ReturnSpeed, true);
	
	if (StaticMeshComponent->GetRelativeLocation().Length() <= 10.0f)
	{
		bIsReturn = false;
	}
}

void AKnife::InitPlayer(ACharacter* NewPlayer)
{
	Player = NewPlayer;
}

void AKnife::OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//E_LOG(LogTemp, Warning, TEXT("AKnife::OnHitBoxBeginOverlap) OverlappedActor : %s"), *OtherActor->GetName());
}
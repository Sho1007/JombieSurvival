// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/ShotGunHitBox.h"

#include <Components/StaticMeshComponent.h>

#include "ShotGunBase.h"

// Sets default values
AShotGunHitBox::AShotGunHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName("NoCollision");
	StaticMeshComponent->SetHiddenInGame(true);
}

void AShotGunHitBox::BeginPlay()
{
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AShotGunHitBox::OnComponentBeginOverlap);
}

void AShotGunHitBox::Init(AShotGunBase* NewShotGun)
{
	ShotGun = NewShotGun;
}

AShotGunBase* AShotGunHitBox::GetShotGun() const
{
	return ShotGun;
}

float AShotGunHitBox::GetKnockBackPower() const
{
	return ShotGun->KnockbackPower;
}

void AShotGunHitBox::Fire()
{
	StaticMeshComponent->SetCollisionProfileName("Projectile", true);
	StaticMeshComponent->SetCollisionProfileName("NoCollision", true);
}

void AShotGunHitBox::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("AShotGunHitBox::OnComponentBeginOverlap) ActorName : %s"), *OtherActor->GetName());
	ShotGun->ApplyDamage(OtherActor);
}
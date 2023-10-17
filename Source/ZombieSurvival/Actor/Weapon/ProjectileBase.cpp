// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/ProjectileBase.h"

#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/DamageEvents.h>

#include "../SpawnManager.h"
#include "../Character/Enemy/ZombieBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<USphereComponent>(TEXT("HitBox"));
	SetRootComponent(HitBox);
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnHitBoxBeginOverlap);
	HitBox->SetCollisionProfileName(TEXT("Projectile"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AProjectileBase::OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AProjectileBase::OnHitBoxBeginOverlap) Overlapped Actor : %s"), *OtherActor->GetName());
	
	//OutHit.GetActor()->TakeDamage(AttackDamage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
	
	// Todo : Effect

	OtherActor->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), GetWorld()->GetFirstPlayerController(), this);
	Disactive();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLifeTime += DeltaTime;

	if (CurrentLifeTime >= MaxLifeTime)
	{
		Disactive();
		return;
	}

	AddActorWorldOffset(GetActorForwardVector() * Speed * DeltaTime);
}

void AProjectileBase::Init(ASpawnManager* NewSpawnManager, int NewObjectIndex)
{
	SpawnManager = NewSpawnManager;
	ObjectIndex = NewObjectIndex;
}

void AProjectileBase::Active()
{
	bIsActived = true;
	HitBox->SetCollisionProfileName(TEXT("Projectile"));
	CurrentLifeTime = 0.0f;
	SetActorTickEnabled(true);

	SetActorHiddenInGame(false);
}

void AProjectileBase::Disactive()
{
	bIsActived = false;
	HitBox->SetCollisionProfileName(TEXT("NoCollision"));
	SetActorTickEnabled(false);

	SetActorHiddenInGame(true);
}

float AProjectileBase::GetKnockbackPower() const
{
	return KnockbackPower;
}

bool AProjectileBase::IsActive() const
{
	return bIsActived;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}
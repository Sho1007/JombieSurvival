// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/PlayerBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include <Components/WidgetComponent.h>

// EnhancedInput
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <InputMappingContext.h>
#include <Engine/EngineTypes.h>

#include "../../../Interface/InteractInterface.h"
#include "../../Weapon/GunBase.h"
#include "../Enemy/ZombieBase.h"
#include "../../PlayerController/InGamePlayerController.h"
#include "../../../Widget/InGame/HPBarWidget.h"
#include "../../../ZombieSurvivalGameInstance.h"

APlayerBase::APlayerBase()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerBase::OnComponentBeginOverlap);

	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidgetComponent"));
	HPBarWidgetComponent->SetupAttachment(RootComponent);
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetDrawSize(FVector2D(130, 15));
	HPBarWidgetComponent->SetPivot(FVector2D(0.5f, -5.0f));
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	// HPBar

	Cast<UHPBarWidget>(HPBarWidgetComponent->GetWidget())->InitPlayer(this);

	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon_R"));
		Gun->SetOwner(this);
		Gun->SetPlayer(this);
	}

	// SetStat

	SetDamageStat();
	SetArmorStat();
	SetSpeedStat();
	SetHealthStat();

	// EnhancedInput
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultContext->IsValidLowLevelFast())
			{
				//UE_LOG(LogTemp, Warning, TEXT("EnhancedInput Debug) Mapping"));
				Subsystem->AddMappingContext(DefaultContext, 0);
			}
		}
	}
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		//UE_LOG(LogTemp, Warning, TEXT("EnhancedInput Debug) Binding"));
		EnhancedInputComponent->BindAction(InputAction_Move, ETriggerEvent::Triggered, this, &APlayerBase::Move);
	}
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult OutHit;
	if (GetController<APlayerController>()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), false, OutHit))
	{
		FVector LookDirection = OutHit.Location - GetActorLocation();
		if (LookDirection.Length() >= MinRotateDistance)
		{
			GetMesh()->SetWorldRotation(FRotator(0, FRotationMatrix::MakeFromX(LookDirection).Rotator().Yaw - 90, 0));
		}
		
		
		//DrawDebugLine(GetWorld(), GetActorLocation(), OutHit.Location, FColor::Yellow, false, 1.0f);
		//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::Tick) MouseLocation : %s, MouseDireciton : %s"), *MouseLocation.ToString(), *MouseDirection.ToString());
	}
}

void APlayerBase::AddExp(int32 NewExp)
{
	SetCurrentExp(CurrentExp + NewExp);

	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::EarnMoeny) MoneyAmount : %d"), MoneyAmount);
}

void APlayerBase::AddBullet_Implementation(int32 NewBulletAmount)
{
	// Todo : Add Bullet To Weapon
	Gun->AddBullet(NewBulletAmount);
	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::AddBullet) BulletAmount : %d"), BulletAmount);
}

float APlayerBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::TakeDamage) DamageAmount : %f"), DamageAmount);

	SetCurrentHealth(CurrentHealth - DamageAmount);

	if (CurrentHealth <= 0.0f && bIsDead == false)
	{
		Die();
	}

	return 0.0f;
}

void APlayerBase::Die()
{
	bIsDead = true;
	CurrentHealth = 0.0f;

	// Todo

	if (AInGamePlayerController* PC = GetController<AInGamePlayerController>())
	{
		PC->ShowGameOverWidget();
		PC->SetPause(true);
	}
}

void APlayerBase::PlayFireMontage()
{
	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::PlayFireMontage) %f"), );
	switch (Gun->GetGunType())
	{
	case EGunType::RIFLE:
		if (RifleFireMontage) PlayAnimMontage(RifleFireMontage);
		break;
	case EGunType::SHOTGUN:
		if (ShotGunFireMontage) PlayAnimMontage(ShotGunFireMontage);
		break;
	}
}

void APlayerBase::LevelUp(FText StatName)
{
	if (StatName.EqualTo(FText::FromName(TEXT("Damage"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::LevelUp) Is Equal To Damage"));
		DamageLevel++;
		SetDamageStat();
	}
	else if (StatName.EqualTo(FText::FromName(TEXT("Armor"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::LevelUp) Is Equal To Armor"));
		ArmorLevel++;
		SetArmorStat();
	}
	else if (StatName.EqualTo(FText::FromName(TEXT("Speed"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::LevelUp) Is Equal To Speed"));
		SpeedLevel++;
		SetSpeedStat();
	}
	else if (StatName.EqualTo(FText::FromName(TEXT("Health"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::LevelUp) Is Equal To Health"));
		HealthLevel++;
		SetHealthStat();
	}

	if (AInGamePlayerController* PC = GetController<AInGamePlayerController>())
	{
		PC->EndLevelUp();
	}
}

float APlayerBase::GetCurrentExp() const
{
	return CurrentExp;
}

float APlayerBase::GetMaxExp() const
{
	return MaxExp;
}

int APlayerBase::GetDamageLevel() const
{
	return DamageLevel;
}

int APlayerBase::GetArmorLevel() const
{
	return ArmorLevel;
}

int APlayerBase::GetSpeedLevel() const
{
	return SpeedLevel;
}

int APlayerBase::GetHealthLevel() const
{
	return HealthLevel;
}

void APlayerBase::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::Move"));
	FVector2D InputVector2D = Value.Get<FVector2D>();
	AddMovementInput(FVector(InputVector2D.X, InputVector2D.Y, 0), Speed);
}

void APlayerBase::SetCurrentHealth(float NewCurrentHealth)
{
	CurrentHealth = NewCurrentHealth;

	OnHPUpdated.ExecuteIfBound(CurrentHealth / MaxHealth);
}

void APlayerBase::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;

	CurrentHealth = CurrentHealth <= MaxHealth ? CurrentHealth : MaxHealth;

	OnHPUpdated.ExecuteIfBound(CurrentHealth / MaxHealth);
}

void APlayerBase::SetCurrentExp(float NewCurrentExp)
{
	CurrentExp = NewCurrentExp;

	OnExpUpdated.ExecuteIfBound(CurrentExp, MaxExp);

	if (CurrentExp >= MaxExp)
	{
		if (AInGamePlayerController* PC = GetController<AInGamePlayerController>())
		{
			PC->LevelUp(CurrentLevel);
		}
		CurrentExp -= MaxExp;
		MaxExp += 100.0f;
		OnExpUpdated.ExecuteIfBound(CurrentExp, MaxExp);
	}
}

void APlayerBase::SetMaxExp(float NewMaxExp)
{
	MaxExp = NewMaxExp;

	OnExpUpdated.ExecuteIfBound(CurrentExp, MaxExp);
}

void APlayerBase::SetDamageStat()
{
	if (UZombieSurvivalGameInstance* Instance = GetGameInstance<UZombieSurvivalGameInstance>())
	{
		FStatData* DamageData = Instance->FindStatData("Damage");

		if (DamageData)
		{
			if (DamageLevel < DamageData->StatArray.Num())
			{
				Gun->SetDamage(DamageData->StatArray[DamageLevel]);
			}
		}
	}
}

void APlayerBase::SetArmorStat()
{
	if (UZombieSurvivalGameInstance* Instance = GetGameInstance<UZombieSurvivalGameInstance>())
	{
		FStatData* ArmorData = Instance->FindStatData("Armor");

		if (ArmorData)
		{
			if (ArmorLevel < ArmorData->StatArray.Num())
			{
				Armor = ArmorData->StatArray[ArmorLevel];
			}
		}
	}
}

void APlayerBase::SetSpeedStat()
{
	if (UZombieSurvivalGameInstance* Instance = GetGameInstance<UZombieSurvivalGameInstance>())
	{
		FStatData* SpeedData = Instance->FindStatData("Speed");

		if (SpeedData)
		{
			if (SpeedLevel < SpeedData->StatArray.Num())
			{
				Speed = SpeedData->StatArray[SpeedLevel];
			}
		}
	}
}

void APlayerBase::SetHealthStat()
{
	if (UZombieSurvivalGameInstance* Instance = GetGameInstance<UZombieSurvivalGameInstance>())
	{
		FStatData* HealthData = Instance->FindStatData("Health");

		if (HealthData)
		{
			if (HealthLevel < HealthData->StatArray.Num())
			{
				SetMaxHealth(HealthData->StatArray[HealthLevel]);
				if (HealthLevel == 0)
				{
					SetCurrentHealth(MaxHealth);
				}
				else
				{
					SetCurrentHealth(CurrentHealth + MaxHealth - HealthData->StatArray[HealthLevel - 1]);
				}
			}
		}
	}
}

void APlayerBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractInterface* Interface = Cast<IInteractInterface>(OtherActor))
	{
		Interface->Interact(this);
	}
}
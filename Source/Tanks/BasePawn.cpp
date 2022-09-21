// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include <Components/ArrowComponent.h>
#include "HealthComponent.h"
#include <Components/BoxComponent.h>
#include "Tanks.h"
#include "Cannon.h"
#include <Components/StaticMeshComponent.h>
#include "Logging/LogMacros.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/AudioComponent.h>
#include "ActorPoolSubsystem.h"
#include "HealthBar.h"
#include "Pawns.h"
#include "SimpleSavingActorSubsystem.h"
#include <Engine/World.h>
#include "InventoryComponentPlugin.h"
#include "SaveActorsSubsystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMesh"));
	SetRootComponent(BaseMesh);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	DestroyingVisualEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Destroying Pawn Visual Effect"));
	DestroyingVisualEffect->SetupAttachment(BaseMesh);

	DestroyingAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Destroying Pawn Audio Effect"));
	DestroyingAudioEffect->SetupAttachment(BaseMesh);

	CannonSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSpawn"));
	CannonSpawnPoint->SetupAttachment(TurretMesh);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddDynamic(this, &ABasePawn::OnDie);
	HealthComponent->OnHealthChanged.AddDynamic(this, &ABasePawn::OnHealthChanged);

	LootSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	LootSpawnPoint->SetupAttachment(BaseMesh);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon(DefaultCannonClass, MaxAmmo);
	CurrentCannonIndex = 0;

	Pawns::AddPawn(this);

	if (GetWorld()->GetFirstPlayerController() != GetController())
	{
		GetWorld()->GetSubsystem<USaveActorsSubsystem>()->SaveActor(GetName(), this);
	}
}

void ABasePawn::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Pawns::DelPawn(this);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthBar)
	{
		if (GetCannon())
		{
			Cast<UHealthBar>(HealthBar->GetWidget())->SetAmmo(((GetCannon()->GetAmmoNow()) * 1.f) / MaxAmmo);
		}
		Cast<UHealthBar>(HealthBar->GetWidget())->SetHealth(HealthComponent->GetHealthState());
	}
}

void ABasePawn::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			float CurHealth = HealthComponent->GetHealth();
			Ar << CurHealth;

			int CurAmmo = Cannons[CurrentCannonIndex]->GetAmmoNow();
			Ar << CurAmmo;

			LocalInventory->Serialize(Ar);

			FVector ActorLocation = GetActorLocation();
			FTransform GunTransform = GetGunTransform();
			FTransform BaseTransform = GetBaseTransform();
			Ar << ActorLocation << GunTransform << BaseTransform;
		}
		else
		{
			float CurHealth;
			Ar << CurHealth;
			HealthComponent->SetHealth(CurHealth);

			int CurAmmo;
			Ar << CurAmmo;
			Cannons[CurrentCannonIndex]->SetAmmoNow(CurAmmo);

			LocalInventory->Serialize(Ar);

			FVector ActorLocation;
			FTransform GunTransform;
			FTransform BaseTransform;
			Ar << ActorLocation << GunTransform << BaseTransform;
			SetActorLocation(ActorLocation);
			SetGunTransform(GunTransform);
			SetBaseTransform(BaseTransform);
		}
	}
}

class ACannon* ABasePawn::GetCannon() const
{
	return Cannons[CurrentCannonIndex];
}

void ABasePawn::OnHealthChanged_Implementation(float DamageAmount)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s taked damage: %f"), *GetName(), DamageAmount);
}

void ABasePawn::OnDie_Implementation()
{
	if (!bIsDestroyed)
	{
		DestroyingVisualEffect->ActivateSystem();
		DestroyingAudioEffect->Play();

		UActorPoolSubsystem* Pool = GetWorld()->GetSubsystem<UActorPoolSubsystem>();
		FTransform SpawnTransform(LootSpawnPoint->GetComponentRotation(), LootSpawnPoint->GetComponentLocation(), FVector::OneVector);
		AAmmoBox* AmmoBox = Cast<AAmmoBox>(Pool->RetreiveActor(LootClass, SpawnTransform));

		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABasePawn::Destroying, DestroyingDelay, false);

		bIsDestroyed = true;
	}
}

void ABasePawn::Destroying()
{
	Destroy();
	for (const auto Cannon : Cannons)
	{
		Cannon->Destroy();
	}

	GetWorld()->GetTimerManager().ClearTimer(DestroyTimerHandle);
}

UInventoryManagerComponent* ABasePawn::GetInventoryManager()
{
	return InventoryManager;
}

UHealthComponent* ABasePawn::GetHealthComponent()
{
	return HealthComponent;
}

void ABasePawn::Fire()
{
	if (!Cannons[CurrentCannonIndex]) return;

	Cannons[CurrentCannonIndex]->Fire();
}

int ABasePawn::GetCurrentAmmo() const
{
	return Cannons[CurrentCannonIndex]->GetAmmoNow();
}

void ABasePawn::SetCurrentAmmo(int InAmmo)
{
	Cannons[CurrentCannonIndex]->SetAmmoNow(InAmmo);
}

bool ABasePawn::GetFriendness()
{
	return bIsFriendly;
}

void ABasePawn::SetFriendness(bool InFriendness)
{
	bIsFriendly = InFriendness;
}

UArrowComponent* ABasePawn::GetCannonSpawnPoint()
{
	return CannonSpawnPoint;
}

void ABasePawn::SetupCannon(TSubclassOf<class ACannon> InCannonClass, int AmmoAmount)
{
	if (InCannonClass)
	{

		ACannon* Cannon = nullptr;

		FActorSpawnParameters Params;
		Params.Instigator = this;
		Params.Owner = this;

		Cannon = GetWorld()->SpawnActor <ACannon>(InCannonClass, Params);
		//UE_LOG(LogTanks, Verbose, TEXT("Spawned new cannon: %s"), *(Cannon->GetName()));

		if (!Cannon)
		{
			return;
		}

		Cannon->AttachToComponent(CannonSpawnPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Cannon->AddAmmo(AmmoAmount);

		bool IsThereNotCannon = !(Cannons.Find(Cannon) + 1);

		if (Cannons.Num() <= MaxCannons || IsThereNotCannon)
		{
			Cannon->SetAmmo(MaxAmmo);
			if (Cannons.Num() == MaxCannons && IsThereNotCannon)
			{
				Cannons[CurrentCannonIndex]->Destroy();
				Cannons.RemoveAt(CurrentCannonIndex);
				Cannons.Insert(Cannon, CurrentCannonIndex);
			}
			else
			{
				if (Cannons.Num())
				{
					Cannons[CurrentCannonIndex]->SetVisibility(false);
				}
				Cannons.Add(Cannon);
				CurrentCannonIndex = (CurrentCannonIndex + 1) % MaxCannons;
			}
			
			//UE_LOG(LogTanks, Verbose, TEXT("Added in cannons new cannon: %s. Ind: %d"), *(Cannon->GetName()), CurrentCannonIndex);
		}
		//UE_LOG(LogTanks, Verbose, TEXT("Cannons[CurrentCannonIndex] now: %s"), *(Cannons[CurrentCannonIndex]->GetName()));
	}
}
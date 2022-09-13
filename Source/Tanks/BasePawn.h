	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AmmoBox.h"
#include <Components/WidgetComponent.h>
#include <Components/ArrowComponent.h>
#include "InventoryCharacter.h"
#include "BasePawn.generated.h"

UCLASS()
class TANKS_API ABasePawn : public AInventoryCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UInventoryManagerComponent* GetInventoryManager();

	class UHealthComponent* GetHealthComponent();

private:
	FTimerHandle DestroyTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* HealthBar;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* LootSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Loot params")
	TSubclassOf<class AAmmoBox> LootClass;

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnHealthChanged(float DamageAmount);

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnDie();

	void Destroying();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DestroyingDelay")
	float DestroyingDelay = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	TSubclassOf<class ACannon> DefaultCannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	int MaxAmmo = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret")
	int MaxCannons = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friendliness")
	bool bIsFriendly = false;

	UPROPERTY()
	int CurrentCannonIndex = 0;

	UPROPERTY()
	bool bIsDestroyed = false;

	UPROPERTY()
	TArray<class ACannon*> Cannons;

	UPROPERTY()
	TArray<class APawn*> Targets;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* DestroyingVisualEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UAudioComponent* DestroyingAudioEffect;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Serialize(FArchive& Ar) override;

	UFUNCTION(BlueprintCallable, Category = "Turret")
	void SetupCannon(TSubclassOf<class ACannon> InCannonClass, int AmmoAmount);

	UFUNCTION(BlueprintCallable, Category = "Turret")
	void Fire();

	int GetCurrentAmmo() const;

	void SetCurrentAmmo(int InAmmo);

	UFUNCTION(BlueprintCallable, Category = "Friendness")
	bool GetFriendness();

	UFUNCTION(BlueprintCallable, Category = "Friendness")
	void SetFriendness(bool InFriendness);

	FTransform GetGunTransform() const
	{
		return TurretMesh->GetRelativeTransform();
	}

	FTransform GetBaseTransform() const
	{
		return BaseMesh->GetRelativeTransform();
	}

	void SetGunTransform(FTransform InTransform)
	{
		TurretMesh->SetRelativeTransform(InTransform);
	}

	void SetBaseTransform(FTransform InTransform)
	{
		BaseMesh->SetRelativeTransform(InTransform);
	}

	UFUNCTION(BlueprintPure, Category = "Turret")
	class ACannon* GetCannon() const;

	UArrowComponent* GetCannonSpawnPoint();

};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "InventoryDataPlugin.h"
#include "SimpleSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{

	GENERATED_BODY()

public:
	
	FCharacterInfo()
	{
	}

	FCharacterInfo(float InHealth, int InAmmo, TMap<int, FInventorySlotInfo>& InItems, FVector InTankLocation, FTransform InGunTransform, FTransform InBaseTransform)
	{
		Health = InHealth;
		Ammo = InAmmo;
		Items = InItems;
		TankLocation = InTankLocation;
		GunTransform = InGunTransform;
		BaseTransform = InBaseTransform;
	}

	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	int Ammo;

	UPROPERTY(BlueprintReadWrite)
	TMap<int, FInventorySlotInfo> Items;

	UPROPERTY(BlueprintReadWrite)
	FVector TankLocation;

	UPROPERTY(BlueprintReadWrite)
	FTransform GunTransform;

	UPROPERTY(BlueprintReadWrite)
	FTransform BaseTransform;
};

USTRUCT(BlueprintType)
struct FEnemyInfo
{

	GENERATED_BODY()

public:
	
	FEnemyInfo()
	{
	}

	FEnemyInfo(float InHealth, int InAmmo, FVector InEnemyLocation, FTransform InGunTransform, FTransform InBaseTransform)
	{
		Health = InHealth;
		Ammo = InAmmo;
		EnemyLocation = InEnemyLocation;
		GunTransform = InGunTransform;
		BaseTransform = InBaseTransform;
	}

	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	int Ammo;

	UPROPERTY(BlueprintReadWrite)
	FVector EnemyLocation;

	UPROPERTY(BlueprintReadWrite)
	FTransform GunTransform;

	UPROPERTY(BlueprintReadWrite)
	FTransform BaseTransform;
};

UCLASS()
class TANKS_API USimpleSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FCharacterInfo> CharInfo;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FEnemyInfo> EnemyInfo;

	void CollectData(UWorld* World);
	void ApplyData(UWorld* World);
};

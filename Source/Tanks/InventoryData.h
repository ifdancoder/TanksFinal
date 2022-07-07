// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UObject/NameTypes.h>
#include <Engine/Texture2D.h>
#include <Engine/StaticMesh.h>
#include <Engine/DataTable.h>
#include "InventoryData.generated.h"

UENUM()
enum class EItemType : uint8
{
	It_Misc,
	It_Currency,
	It_Equip,
	It_Consumable
};

UENUM()
enum class EItemRarity : uint8
{
	Ir_Common,
	Ir_Rare,
	Ir_Epic,
	Ir_All
};

UENUM()
enum class EEquipSlot : uint8
{
	Es_Head,
	Es_Body,
	Es_Track
};

class UInventoryCellWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget*, UInventoryCellWidget*)

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="General")
	FName Id;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EEquipSlot EquipSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int Armor;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int Intelligence;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int HealthBuff;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EItemRarity Rare;
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "General")
	FName Id = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	int Count;
};
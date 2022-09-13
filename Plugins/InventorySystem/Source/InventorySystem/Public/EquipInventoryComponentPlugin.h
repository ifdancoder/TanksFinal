// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponentPlugin.h"
#include "EquipInventoryComponentPlugin.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UEquipInventoryComponent();

	virtual int GetMaxItemAmount(int SlotIndex, const FInventoryItemInfo& InItem) override;

	virtual void SetItem(int SlotIndex, const FInventorySlotInfo& Item) override;

	virtual void ClearItem(int SlotIndex) override;

	UPROPERTY(EditAnywhere)
	TMap<int, EEquipSlot> EquipSlots;
};

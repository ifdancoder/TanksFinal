// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryDataPlugin.h"
#include "InventoryComponentPlugin.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<int, FInventorySlotInfo> Items;

	class UInventoryManagerComponent* ParentManager;

public:
	
	void SetManager(class UInventoryManagerComponent* InParent);

	const FInventorySlotInfo* GetItem(int SlotIndex) const;

	virtual void SetItem(int SlotIndex, const FInventorySlotInfo& Item);

	virtual void ClearItem(int SlotIndex);

	virtual int GetMaxItemAmount(int SlotIndex, const FInventoryItemInfo& InItem);

	const TMap<int, FInventorySlotInfo>& GetItems() const;

	TMap<int, FInventorySlotInfo>& GetItemsForSaving();

	void SetItems(TMap<int, FInventorySlotInfo>& InItems);

	int GetItemsNum() const;

	virtual void Serialize(FArchive& Ar) override;
};

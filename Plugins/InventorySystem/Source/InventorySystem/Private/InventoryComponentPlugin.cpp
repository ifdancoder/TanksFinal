// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponentPlugin.h"
#include "InventoryManagerComponentPlugin.h"

void UInventoryComponent::SetManager(class UInventoryManagerComponent* InParent)
{
	ParentManager = InParent;
}

const FInventorySlotInfo* UInventoryComponent::GetItem(int SlotIndex) const
{
	return Items.Find(SlotIndex);
}

void UInventoryComponent::SetItem(int SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::ClearItem(int SlotIndex)
{
	Items.Remove(SlotIndex);
}

int UInventoryComponent::GetMaxItemAmount(int SlotIndex, const FInventoryItemInfo& InItem)
{
	FInventorySlotInfo* SlotPtr = Items.Find(SlotIndex);

	if (SlotPtr == nullptr || SlotPtr->Id == InItem.Id)
	{
		return 0;
	}

	return -1;
}

const TMap<int, FInventorySlotInfo>& UInventoryComponent::GetItems() const
{
	return Items;
}

TMap<int, FInventorySlotInfo>& UInventoryComponent::GetItemsForSaving()
{
	return Items;
}

void UInventoryComponent::SetItems(TMap<int, FInventorySlotInfo>& InItems)
{
	Items = InItems;
	ParentManager->ReInit();
}

int UInventoryComponent::GetItemsNum() const
{
	return Items.Num();
}

void UInventoryComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 ItemsCount = Items.Num();
			Ar << ItemsCount;
			for (auto Item : Items)
			{
				Ar << Item.Key;
				Ar << Item.Value.Count;
				Ar << Item.Value.Id;
			}
		}
		else
		{
			Items.Reset();
			int32 ItemsCount;
			Ar << ItemsCount;
			int32 Key;
			FInventorySlotInfo Info;
			for (int32 i = 0; i < ItemsCount; ++i)
			{
				Ar << Key;
				Ar << Info.Count;
				Ar << Info.Id;
				Items.Add(Key, Info);
			}
			ParentManager->ReInit();
		}
	}
}


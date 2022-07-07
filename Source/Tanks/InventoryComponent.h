// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryData.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<int, FInventorySlotInfo> Items;
		
public:
	const FInventorySlotInfo* GetItem(int SlotIndex) const;

	virtual void SetItem(int SlotIndex, const FInventorySlotInfo& Item);
	
	virtual void ClearItem(int SlotIndex);

	virtual int GetMaxItemAmount(int SlotIndex, const FInventoryItemInfo& InItem);

	const TMap<int, FInventorySlotInfo>& GetItems() const;

	int GetItemsNum() const;
};

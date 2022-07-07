// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EquipInterface.h"
#include "InventoryCharacter.generated.h"

class UInventoryComponent;
class UEquipInventoryComponent;
class UInventoryManagerComponent;

UCLASS()
class TANKS_API AInventoryCharacter : public APawn, public IEquipInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInventoryCharacter();

protected:

	virtual void BeginPlay() override;

	virtual void EquipItem(EEquipSlot Slot, FName ItemId) override;

	virtual void UnequipItem(EEquipSlot Slot, FName ItemId) override;
	
	UStaticMeshComponent* GetEquipComponent(EEquipSlot EquipSlot);

	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent* LocalInventory;

	UPROPERTY(EditDefaultsOnly)
	UEquipInventoryComponent* EquipInventory;

	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent* InventoryManager;
};

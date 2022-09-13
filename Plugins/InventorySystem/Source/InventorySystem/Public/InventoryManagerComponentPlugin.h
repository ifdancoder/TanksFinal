// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryDataPlugin.h"
#include "InventoryManagerComponentPlugin.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	int CurrentHeal;

	UPROPERTY()
	class UInventoryComponent* LocalInventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere)
	int MinInventorySize = 20;

	UPROPERTY()
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget> EquipWidgetClass;

	UPROPERTY()
	class UInventoryWidget* EquipWidget;

public:

	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
	// Sets default values for this component's properties

	void Init(UInventoryComponent* InInventoryComponent);

	void ReInit();

	void InitChest(UInventoryComponent* InInventoryComponent);

	void InitEquip(UInventoryComponent* InInventoryComponent);

	const FInventoryItemInfo* GetItemData(const FName& Id);

	//void CollapseByRarity(EItemRarity ItemRarity);

	void MySwap(UInventoryCellWidget* From, UInventoryCellWidget* To);

	int GetCurrentHeal() const { return CurrentHeal; }

	void SetCurrentHeal(int val) { CurrentHeal = val; }
};
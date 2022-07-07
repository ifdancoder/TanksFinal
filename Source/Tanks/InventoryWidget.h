// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryCellWidget;
class UInventoryComponent;
class UButton;

/**
 * 
 */
UCLASS()
class TANKS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void Init(int ItemsCount);

	void InitChest(int ItemsCount);

	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int SlotIndex);

	bool AddToChestItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int SlotIndex);

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UInventoryComponent* ParentInventory;

protected:

	UPROPERTY()
	int ItemsInRow = 5;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidgetOptional))
	UUniformGridPanel* CellsPanel;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
	UUniformGridPanel* ChestCellsPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
	UInventoryCellWidget* CoinCell;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
	UButton* AllButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
	UButton* CommonButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
	UButton* RareButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
	UButton* EpicButton;

	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCellWidget*> CellWidgets;

	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCellWidget*> ChestCellWidgets;

	UInventoryCellWidget* CreateCell();
	UInventoryCellWidget* CreateChestCell();

	UFUNCTION()
	void OnAllClicked();

	UFUNCTION()
	void OnCommonClicked();

	UFUNCTION()
	void OnRareClicked();

	UFUNCTION()
	void OnEpicClicked();

	void SortCells();

	void CollapseByRarity(EItemRarity Rarity);

	void InitCell(UInventoryCellWidget* NewCell);

	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
};

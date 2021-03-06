// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"
#include "HealthComponent.h"
#include "InventoryCellWidget.generated.h"

class UImage;
class UTextBlock;
struct FInventorySlotInfo;
struct FInventoryItemInfo;
class UInventoryWidget;
class UInventoryComponent;

/**
 * 
 */
UCLASS()
class TANKS_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* CountText;

	bool bHasItem = false;

	UPROPERTY()
	FInventoryItemInfo ItemInfo;

	UPROPERTY()
	FInventorySlotInfo Item;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditAnywhere)
	bool bCanDrag = true;

public:

	FInventoryItemInfo* UInventoryCellWidget::GetItemInfo();

	UImage* GetImage() const;

	bool HasItem() const;

	bool AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info);

	void Use();

	void Clear();

	void CollapseIt();

	void UnCollapseIt();

	const FInventorySlotInfo& GetItem() const;

	UPROPERTY(EditAnywhere)
	int IndexInInventory = INDEX_NONE;

	UPROPERTY()
	UInventoryWidget* ParentInventoryWidget;

	FOnItemDrop OnItemDrop;

	UInventoryComponent* GetParentInventory() const;
};

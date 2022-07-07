// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "InventoryWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "InventoryComponent.h"
#include "TankDragDropOperation.h"
#include "HealthComponent.h"
#include "BasePawn.h"

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	if (bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && ItemInfo.Type == EItemType::It_Consumable)
	{
		Use();
	}

	return FReply::Handled();
}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UTankDragDropOperation::StaticClass());

	auto* DragVisual = CreateWidget<UInventoryCellWidget>(GetWorld(), GetClass());

	if (DragVisual && DragVisual->ItemImage)
	{
		DragVisual->ItemImage->SetBrushFromTexture(ItemInfo.Icon.LoadSynchronous());
		DragVisual->ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		DragVisual->CountText->SetText(CountText->Text);
	}

	if (OutOperation)
	{
		auto InventoryDragDropOperation = Cast<UTankDragDropOperation>(OutOperation);

		if (InventoryDragDropOperation)
		{
			InventoryDragDropOperation->SourceCell = this;
			InventoryDragDropOperation->DefaultDragVisual = DragVisual;

		}
	}
}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	auto InventoryDragDropOperation = Cast<UTankDragDropOperation>(InOperation);

	if (InventoryDragDropOperation && InventoryDragDropOperation->SourceCell != this)
	{

		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDragDropOperation->SourceCell, this);
			return true;
		}
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FInventoryItemInfo* UInventoryCellWidget::GetItemInfo()
{
	return &ItemInfo;
}

UImage* UInventoryCellWidget::GetImage() const
{
	return ItemImage;
}

bool UInventoryCellWidget::HasItem() const
{
	return bHasItem;
}

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(InSlot.Count)));
	}

	ItemInfo = Info;

	bHasItem = true;
	Item = InSlot;

	return true;
}

void UInventoryCellWidget::Use()
{
	if (ItemInfo.HealthBuff != 0)
	{
		FDamageData Healing;
		Healing.DamageValue = -ItemInfo.HealthBuff;
		Cast<ABasePawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetHealthComponent()->TakeDamage(Healing);
		Item.Count--;
		if (Item.Count < 1)
		{
			Clear();
		}
		else
		{
			AddItem(Item, ItemInfo);
		}
	}
}

void UInventoryCellWidget::Clear()
{
	CollapseIt();

	Item = FInventorySlotInfo();
	bHasItem = false;
}

void UInventoryCellWidget::CollapseIt()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventoryCellWidget::UnCollapseIt()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

const FInventorySlotInfo& UInventoryCellWidget::GetItem() const
{
	return Item;
}

UInventoryComponent* UInventoryCellWidget::GetParentInventory() const
{
	return ParentInventoryWidget ? ParentInventoryWidget->ParentInventory : nullptr;
}

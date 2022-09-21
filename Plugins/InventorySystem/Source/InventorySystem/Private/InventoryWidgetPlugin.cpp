// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetPlugin.h"
#include "Components/Image.h"
#include <Components/UniformGridPanel.h>
#include "InventoryCellWidgetPlugin.h"
#include "InventoryManagerComponentPlugin.h"
#include <Components/Button.h>


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto* Cell : CellWidgets)
	{
		InitCell(Cell);
	}

	for (auto* Cell : ChestCellWidgets)
	{
		InitCell(Cell);
	}

	if (AllButton)
	{
		AllButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnAllClicked);
	}

	if (CommonButton)
	{
		CommonButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCommonClicked);
	}

	if (RareButton)
	{
		RareButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnRareClicked);
	}

	if (EpicButton)
	{
		EpicButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnEpicClicked);
	}
}



void UInventoryWidget::Init(int ItemsCount)
{
	if (CellsPanel)
	{
		CellsPanel->ClearChildren();

		for (int i = 0; i < ItemsCount; i++)
		{
			if (auto* Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				CellsPanel->AddChildToUniformGrid(Cell, i / ItemsInRow, i % ItemsInRow);
			}
		}
	}
}

void UInventoryWidget::InitChest(int ItemsCount)
{
	if (ChestCellsPanel) {
		ChestCellsPanel->ClearChildren();

		for (int i = 0; i < ItemsCount; i++) {

			if (auto* Cell = CreateChestCell()) {
				Cell->IndexInInventory = i;
				ChestCellsPanel->AddChildToUniformGrid(Cell, i / ItemsInRow, i % ItemsInRow);
			}
		}
	}
}

bool UInventoryWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info, int SlotIndex)
{
	if (Info.Type == EItemType::It_Currency)
	{
		if (CoinCell)
		{
			return CoinCell->AddItem(InSlot, Info);
		}
	}

	if (CellsPanel)
	{
		UInventoryCellWidget* Found = nullptr;
		UInventoryCellWidget** FoundPtr = CellWidgets.FindByPredicate([SlotIndex](UInventoryCellWidget* Cell)
			{
				return Cell && Cell->IndexInInventory == SlotIndex;
			});

		if (FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for (auto* Cell : CellWidgets)
			{
				if (!Cell->HasItem())
				{
					Found = Cell;
					break;
				}
			}
		}

		if (Found)
		{
			return Found->AddItem(InSlot, Info);
		}
	}

	return false;
}

bool UInventoryWidget::AddToChestItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int SlotIndex)
{
	if (ChestCellsPanel) {
		UInventoryCellWidget* Found = nullptr;
		UInventoryCellWidget** FoundPtr = ChestCellWidgets.FindByPredicate([SlotIndex](UInventoryCellWidget* Cell)
			{
				return Cell && Cell->IndexInInventory == SlotIndex;
			});
		if (FoundPtr) {
			Found = *FoundPtr;
		}
		else {
			for (auto* Cell : ChestCellWidgets) {
				if (!Cell->HasItem()) {
					Found = Cell;
					break;
				}
			}
		}
		if (Found) {
			return Found->AddItem(SlotInfo, ItemInfo);
		}
	}
	return false;
}

void UInventoryWidget::SetCurrentHeal(int val)
{
	ParentComponent->SetCurrentHeal(val);
}

UInventoryCellWidget* UInventoryWidget::CreateCell()
{
	if (CellWidgetClass)
	{
		auto* Cell = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(Cell);
		InitCell(Cell);

		return Cell;
	}

	return nullptr;
}

UInventoryCellWidget* UInventoryWidget::CreateChestCell()
{
	if (CellWidgetClass) {
		auto* Cell = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
		ChestCellWidgets.Add(Cell);
		InitCell(Cell);

		return Cell;
	}
	return nullptr;
}

void UInventoryWidget::OnAllClicked()
{
	CollapseByRarity(EItemRarity::Ir_All);
}

void UInventoryWidget::OnCommonClicked()
{
	CollapseByRarity(EItemRarity::Ir_Common);
}

void UInventoryWidget::OnRareClicked()
{
	CollapseByRarity(EItemRarity::Ir_Rare);
}

void UInventoryWidget::OnEpicClicked()
{
	CollapseByRarity(EItemRarity::Ir_Epic);
}

void UInventoryWidget::SortCells()
{
	/*bool swapp = true;
	auto a = CellsPanelanel->GetAllChildren();
	for (int j = 0; swapp && j < a.Num(); j++)
	{
		swapp = false;
		for (int i = 0; i < a.Num() - 1; i++)
		{
			if (Cast<UInventoryCellWidget>(a[i])->GetImage()->GetVisibility() == ESlateVisibility::Collapsed &&
				Cast<UInventoryCellWidget>(a[i + 1])->GetImage()->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
			{
				Swap(*a[i], *(a[i + 1]));
				swapp = true;
			}
		}
	}*/

	for (auto* i : CellsPanel->GetAllChildren()) {
		for (auto* j : CellsPanel->GetAllChildren()) {
			if (i > j)
				continue;
			auto* a = Cast<UInventoryCellWidget>(i);
			auto* b = Cast<UInventoryCellWidget>(j);
			if (a->GetImage()->GetVisibility() != ESlateVisibility::Collapsed)
				break;
			if (b->GetImage()->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
				Swap(i, j);
		}
	}
}

void UInventoryWidget::CollapseByRarity(EItemRarity Rarity)
{
	for (auto* Cell : CellsPanel->GetAllChildren())
	{
		UInventoryCellWidget* NewCell = Cast<UInventoryCellWidget>(Cell);
		if (Rarity != EItemRarity::Ir_All && NewCell->GetItemInfo()->Rare != Rarity)
		{
			NewCell->CollapseIt();
		}
		else
		{
			NewCell->UnCollapseIt();
		}
	}

	SortCells();
}

void UInventoryWidget::InitCell(UInventoryCellWidget* NewCell)
{
	if (NewCell)
	{
		NewCell->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		NewCell->ParentInventoryWidget = this;
	}
}

void UInventoryWidget::OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	OnItemDrop.Broadcast(From, To);
}

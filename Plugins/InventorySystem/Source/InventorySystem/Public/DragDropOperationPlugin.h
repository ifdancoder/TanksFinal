// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryCellWidgetPlugin.h"

#include "DragDropOperationPlugin.generated.h"

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UTankDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
		UInventoryCellWidget* SourceCell;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryCellWidget.h"

#include "TankDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UTankDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UInventoryCellWidget* SourceCell;
};

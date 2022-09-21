// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleSavingGameInstance.generated.h"

class USimpleSavingManager;

UCLASS()
class TANKS_API USimpleSavingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject))
	static USimpleSavingManager* GetSaveManager(UObject* WorldContextObject);

protected:
	UPROPERTY()
	USimpleSavingManager* SaveManager;
};

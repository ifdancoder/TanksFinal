// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameInfo.generated.h"

UCLASS()
class SAVESYSTEM_API USaveGameInfo : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float TestFloat;

	UPROPERTY()
	TArray<uint8> Bytes;

	void CollectData(UWorld* World);
	void ApplyData(UWorld* World);

	
};

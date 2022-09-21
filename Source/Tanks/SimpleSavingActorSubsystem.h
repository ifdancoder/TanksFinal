// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SimpleSavingActorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API USimpleSavingActorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	protected:

	UPROPERTY()
	TMap<FString, AActor*> SavedActors;

	public:

	void SaveActor(FString Name, AActor* EnemyPtr) { SavedActors.Add(Name, EnemyPtr); }

	TMap<FString, AActor*> GetEnemies() const { return SavedActors; }



};

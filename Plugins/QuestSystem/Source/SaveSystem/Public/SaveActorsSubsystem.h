// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveActorsSubsystem.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class SAVESYSTEM_API USaveActorsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


protected:
	UPROPERTY()
	TMap<FString, AActor*> SavedActors;

public:
	void SaveActor(FString Name, AActor* EnemyPtr){SavedActors.Add(Name, EnemyPtr);}
	TMap<FString, AActor*> GetEnemies() const {return SavedActors;}

	virtual void Serialize(FArchive& Ar) override;
	
};

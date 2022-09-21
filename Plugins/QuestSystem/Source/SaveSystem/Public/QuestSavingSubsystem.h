// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestSavingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SAVESYSTEM_API UQuestSavingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TMap<FString, AActor*> QuestGiverActors;

public:
	void SaveQuestGiverActor(FString Name, AActor* EnemyPtr) { QuestGiverActors.Add(Name, EnemyPtr); }

	TMap<FString, AActor*> GetQuestGiverActors() const { return QuestGiverActors; }

	virtual void Serialize(FArchive& Ar) override;
	
};

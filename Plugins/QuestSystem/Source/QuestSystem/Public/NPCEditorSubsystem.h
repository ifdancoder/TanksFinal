// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "QuestGiverActor.h"
#include "NPCEditorSubsystem.generated.h"

/**
 *
 */
UCLASS()
class QUESTSYSTEM_API UNPCEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TArray<AQuestGiverActor*> QuestGiverActors;

	UPROPERTY()
		TMap<AActor*, TSubclassOf<AActor>> Actors;

public:
	void AddQuestGiverActor(AQuestGiverActor* QuestGiver) { QuestGiverActors.Add(QuestGiver); }

	TArray<AQuestGiverActor*> GetQuestGiverActors() const { return QuestGiverActors; }

	void AddResourceActor(AActor* ResourceActor, TSubclassOf<AActor> ActorClass) { Actors.Add(ResourceActor, ActorClass); }

	TArray<AActor*> FindActorsOfClass(TSubclassOf<AActor> ActorClass);

	void RemoveResourceActor(AActor* Actor);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourcesManagerSubsystem.generated.h"

/**
 *
 */
UCLASS()
class QUESTSYSTEM_API UResourcesManagerSubsystem : public UWorldSubsystem
{	
	GENERATED_BODY()

private:
	UPROPERTY()
		TMap<AActor*, TSubclassOf<AActor>> Actors;



public:

	void AddResourceActor(AActor* ResourceActor, TSubclassOf<AActor> ActorClass) { Actors.Add(ResourceActor, ActorClass); }

	TArray<AActor*> FindActorsOfClass(TSubclassOf<AActor> ActorClass);

	void RemoveResourceActor(AActor* Actor);



};

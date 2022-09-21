// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcesManagerSubsystem.h"

TArray<AActor*> UResourcesManagerSubsystem::FindActorsOfClass(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> ActorsToReturn;
	for (auto Actor : Actors)
	{
		if (Actor.Value == ActorClass)
		{
			ActorsToReturn.Add(Actor.Key);
		}
	}

	return ActorsToReturn;
}

void UResourcesManagerSubsystem::RemoveResourceActor(AActor* Actor)
{
		if (Actors.Contains(Actor))
	{
		Actors.Remove(Actor);
	}
}

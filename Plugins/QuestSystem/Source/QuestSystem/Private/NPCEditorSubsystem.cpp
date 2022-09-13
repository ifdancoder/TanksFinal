// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEditorSubsystem.h"

TArray<AActor*> UNPCEditorSubsystem::FindActorsOfClass(TSubclassOf<AActor> ActorClass)
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

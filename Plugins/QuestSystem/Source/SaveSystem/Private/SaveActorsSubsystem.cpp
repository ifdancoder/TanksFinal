// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveActorsSubsystem.h"

void USaveActorsSubsystem::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 ActorsCount = SavedActors.Num();
			Ar << ActorsCount;
			for (auto Actor : SavedActors)
			{
				Ar << Actor.Key;
				Actor.Value->Serialize(Ar);
			}
		}
		else
		{
			int32 ActorsCount;
			Ar << ActorsCount;
			FString Key;
			for (int32 i = 0; i < ActorsCount; ++i)
			{
				Ar << Key;
				for (auto Actor : SavedActors)
				{
					if (Key == Actor.Key)
					{
						Actor.Value->Serialize(Ar);
					}
				}
			}
		}
	}
}

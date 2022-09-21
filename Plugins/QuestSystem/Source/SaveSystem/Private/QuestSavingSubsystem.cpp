// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSavingSubsystem.h"

void UQuestSavingSubsystem::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 ActorsCount = QuestGiverActors.Num();
			Ar << ActorsCount;
			for (auto Actor : QuestGiverActors)
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
				for (auto Actor : QuestGiverActors)
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "Objective.h"
#include "QuestGiverActor.h"


// Sets default values
AQuestActor::AQuestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestActor::BeginPlay()
{
	Super::BeginPlay();

	if (PreviousQuest)
	{
		auto* Parent = GetAttachParentActor();
		if (auto* QuestGiver = Cast<AQuestGiverActor>(Parent))
		{
			PreviousQuest->OnQuestStatusChanged.AddDynamic(QuestGiver, &AQuestGiverActor::HasAvailableQuests);
		}
	}
}

// Called every frame
void AQuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestActor::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 ObjectivesCount = Objectives.Num();
			Ar << ObjectivesCount;
			for (auto Objective : Objectives)
			{
				FString Key = Objective->GetName();
				Ar << Key;
				Objective->Serialize(Ar);
			}
		}
		else
		{
			int32 ObjectivesCount;
			Ar << ObjectivesCount;
			FString Key;
			for (int32 i = 0; i < ObjectivesCount; ++i)
			{
				Ar << Key;
				for (auto Objective : Objectives)
				{
					if (Key == Objective->GetName())
					{
						Objective->Serialize(Ar);
					}
				}
			}
		}
		Ar << bIsTaken;
		Ar << bIsCompleted;
	}
}

void AQuestActor::TakeQuest(AActor* Character)
{
	if (bIsTaken)
	{
		return;
	}

	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		auto* Objective = Objectives[i];
		if (Objective == nullptr)
		{
			continue;
		}

		Objective->ActivateObjective(Character);
		Objective->bCanBeCompleted = i == 0 || !bKeepObjectivesOrder;
		Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);
	}
	bIsTaken = true;
	OnQuestStatusChanged.Broadcast();
}

void AQuestActor::OnObjectiveCompleted(UObjective* Objective)
{
	if (bKeepObjectivesOrder)
	{
		int32 Index;
		if (Objectives.Find(Objective, Index) && Objectives.IsValidIndex(Index + 1))
		{
			Objectives[Index + 1]->bCanBeCompleted = true;
		}
		else
		{
			bIsCompleted = true;
			OnQuestStatusChanged.Broadcast();
		}
	}
	else
	{
		int32 IncompleteCount = 0;
		for (int32 i = 0; i < Objectives.Num(); i++)
		{
			if (!Objectives[i]->bIsCompleted)
			{
				IncompleteCount++;
				break;
			}
		}
		if (IncompleteCount == 0)
		{
			bIsCompleted = true;
			OnQuestStatusChanged.Broadcast();
		}
	}

	OnQuestObjectiveStatusChanged.Broadcast(this);
}

bool AQuestActor::IsAvailable()
{
	if (!bIsTaken && !bIsCompleted && !PreviousQuest)
	{
		return true;
	}
	if (!bIsTaken && !bIsCompleted && PreviousQuest && PreviousQuest->bIsCompleted)
	{
		return true;
	}
	return false;

}


void AQuestActor::UpdateLocation()
{
	AActor* ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQuestActor::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));
}

void AQuestActor::AddLocationObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));
}

void AQuestActor::AddCollectionObjective()
{
	Objectives.Add(NewObject<UCollectionObjective>(this));
}


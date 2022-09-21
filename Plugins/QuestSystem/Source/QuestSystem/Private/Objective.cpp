// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"

#include "CollectableObject.h"
#include "InteractableObject.h"
#include "LocationMarker.h"
#include "ResourcesManagerSubsystem.h"
#include "ToolBuilderUtil.h"
#include "Kismet/GameplayStatics.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Ot_Interact;
}

void UInteractionObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	if (auto* InteractTarget = Cast<IInteractableObject>(Target))
	{
		InteractTarget->OnInteractionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		);
	}
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Ot_Location;
}

void ULocationObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	if (auto* InteractTarget = Cast<ILocationMarker>(Marker))
	{
		InteractTarget->OnLocationReached.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		);
	}
}

UCollectionObjective::UCollectionObjective()
{
	Type = EObjectiveType::Ot_Collect;
}

void UCollectionObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	auto ResourcesManager = GetWorld()->GetSubsystem<UResourcesManagerSubsystem>();
	TArray<AActor*> ActorsToCollect = ResourcesManager->FindActorsOfClass(CollectableActorClass);
	//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CollectableActorClass, ActorsToCollect);

	for (int32 i = 0; i < ActorsToCollect.Num(); i++)
	{
		if (ICollectableObject* InteractTarget = Cast<ICollectableObject>(ActorsToCollect[i]))
		{
			InteractTarget->OnCollectionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
				{
					CollectionCount++;
					UE_LOG(LogTemp, Warning, TEXT("Count = %d"), CollectionCount);
					if (bCanBeCompleted && Instigator == InteractInstigator && CollectionCount == CountToCollect)
					{
						bIsCompleted = true;
						OnObjectiveCompleted.Broadcast(this);
					}
				}
			);
		}
	}
}

void UObjective::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		Ar << bCanBeCompleted;
		Ar << bIsCompleted;
	}
}

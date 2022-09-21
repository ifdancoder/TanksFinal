// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestListComponent.h"

#include "CurrentObjectives.h"
#include <Kismet/GameplayStatics.h>
#include "Quest.h"
#include "QuestList.h"


// Sets default values for this component's properties
UQuestListComponent::UQuestListComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestListComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentObjectivesWidgetClass)
	{
		UCurrentObjectives* CurrentObjectivesWidget = CreateWidget<UCurrentObjectives>(GetWorld(), CurrentObjectivesWidgetClass);
		OnActiveQuestChanged.AddUObject(CurrentObjectivesWidget, &UCurrentObjectives::SetCurrentObjectives);
		CurrentObjectivesWidget->AddToViewport();
	}

}

void UQuestListComponent::AddQuest(AQuestActor* Quest)
{
	if (Quest)
	{
		AcceptedQuests.AddUnique(Quest);
		Quest->TakeQuest(GetOwner());
		Quest->OnQuestObjectiveStatusChanged.AddLambda([this](AQuestActor* QuestActor)
			{
				if (ActiveQuest == QuestActor)
				{
					OnActiveQuestChanged.Broadcast(QuestActor);
				}
			}
		);
	}
}

void UQuestListComponent::SetActiveQuest(AQuestActor* Quest)
{
	if (AcceptedQuests.Contains(Quest))
	{
		ActiveQuest = Quest;
		OnActiveQuestChanged.Broadcast(Quest);
	}
}

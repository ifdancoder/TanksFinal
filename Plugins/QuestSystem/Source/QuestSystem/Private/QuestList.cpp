// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestList.h"

#include "QuestDescription.h"
#include "QuestListComponent.h"
#include "QuestListEntry.h"
#include "Components/ScrollBox.h"

void UQuestList::Init(UQuestListComponent* QuestList)
{
	if (QuestList && QuestEntryClass)
	{
		for (AQuestActor* Quest : QuestList->GetQuests())
		{
			UScrollBox* Scroll = Quest->IsStoryQuest() ? StoryQuestsList : SideQuestsList;

			if (Scroll)
			{
				UQuestListEntry* QuestEntry = CreateWidget<UQuestListEntry>(this, QuestEntryClass);
				QuestEntry->SetQuestText(Quest->Name);
				QuestEntry->OnQuestChosen.BindUObject(QuestList, &UQuestListComponent::SetActiveQuest, Quest);
				QuestEntries.Add(Quest, QuestEntry);
				Scroll->AddChild(QuestEntry);
			}
		}
		OnActiveQuestChanged(QuestList->GetActiveQuest());
		QuestList->OnActiveQuestChanged.AddUObject(this, &UQuestList::OnActiveQuestChanged);
	}
}

void UQuestList::OnActiveQuestChanged(AQuestActor* ActiveQuest)
{
	if (ActiveQuestDescription)
	{
		ActiveQuestDescription->Init(ActiveQuest);
		ActiveQuestDescription->SetVisibility(ActiveQuest ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

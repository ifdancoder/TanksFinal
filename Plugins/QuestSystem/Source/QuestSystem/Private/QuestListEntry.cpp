// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestListEntry.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UQuestListEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectQuestButton)
	{
		SelectQuestButton->OnReleased.AddDynamic(this, &ThisClass::UQuestListEntry::SelectQuest);
	}
}

void UQuestListEntry::SetQuestText(const FText& Text)
{
	if (QuestText)
	{
		QuestText->SetText(Text);
	}
}

void UQuestListEntry::SelectQuest()
{
	OnQuestChosen.ExecuteIfBound();
}

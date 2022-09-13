// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestDescription.h"

#include "Quest.h"
#include "Components/TextBlock.h"
#include "ObjectiveWidget.h"
#include "Components/ScrollBox.h"

void UQuestDescription::Init(AQuestActor* Quest)
{
	if (Quest)
	{
		if (NameText)
		{
			NameText->SetText(Quest->Name);
		}

		if (DescriptionText)
		{
			DescriptionText->SetText(Quest->Description);
		}

		if (ObjectiveWidgetClass && ObjectiveList)
		{
			ObjectiveList->ClearChildren();
			for (auto* Objective : Quest->GetObjectives())
			{
				UObjectiveWidget* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
				ObjectiveWidget->Init(Objective);
				ObjectiveList->AddChild(ObjectiveWidget);
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentObjectives.h"
#include "Objective.h"
#include "ObjectiveWidget.h"
#include "Quest.h"
#include "Components/VerticalBox.h"

void UCurrentObjectives::SetCurrentObjectives(AQuestActor* Quest)
{
	if (ObjectivesList && ObjectiveWidgetClass)
	{
		ObjectivesList->ClearChildren();
		for (UObjective* Objective : Quest->GetObjectives())
		{
			UObjectiveWidget* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
			ObjectiveWidget->Init(Objective);
			ObjectivesList->AddChildToVerticalBox(ObjectiveWidget);
		}
	}
}

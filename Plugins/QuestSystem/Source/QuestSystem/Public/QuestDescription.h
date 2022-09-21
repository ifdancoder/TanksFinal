// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "QuestDescription.generated.h"

class AQuestActor;
class UTextBlock;
class UScrollBox;
class UObjectiveWidget;

UCLASS()
class QUESTSYSTEM_API UQuestDescription : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(AQuestActor* Quest);

protected:

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* NameText;

	UPROPERTY(meta = (BindWidgetOptional))
		UScrollBox* ObjectiveList;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* DescriptionText;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;
};

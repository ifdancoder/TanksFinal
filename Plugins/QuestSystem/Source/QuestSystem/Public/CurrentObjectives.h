// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrentObjectives.generated.h"

class UObjectiveWidget;
class UVerticalBox;
class AQuestActor;

UCLASS()
class QUESTSYSTEM_API UCurrentObjectives : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

	UPROPERTY(meta = (BindWidgetOptional))
	UVerticalBox* ObjectivesList;

public:
	UFUNCTION()
	void SetCurrentObjectives(AQuestActor* Quest);
};

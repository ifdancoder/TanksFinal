// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest.h"
#include "Components/ActorComponent.h"
#include "QuestListComponent.generated.h"

class UCurrentObjectives;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveQuestChanged, AQuestActor*)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestListComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuestListComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void AddQuest(AQuestActor* Quest);

	const TArray<AQuestActor*>& GetQuests() { return AcceptedQuests; }

	AQuestActor* GetActiveQuest() const { return ActiveQuest; }

	void SetActiveQuest(AQuestActor* Quest);

	FOnActiveQuestChanged OnActiveQuestChanged;

protected:
	
	class UQuestList* OurQuestList;

	UPROPERTY()
	TArray<AQuestActor*> AcceptedQuests;

	UPROPERTY()
	AQuestActor* ActiveQuest;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCurrentObjectives> CurrentObjectivesWidgetClass;

};

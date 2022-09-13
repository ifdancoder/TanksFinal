// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestObjectiveStatusChanged, AQuestActor*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestStatusChanged);

class UObjective;

UCLASS()
class QUESTSYSTEM_API AQuestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Serialize(FArchive& Ar) override;

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TArray<UObjective*> Objectives;

	TArray<UObjective*> GetObjectives() const { return Objectives; }

	UPROPERTY(EditAnywhere)
	bool bIsStoryQuest = true;

	UPROPERTY(EditAnywhere)
	bool bKeepObjectivesOrder = true;

	UPROPERTY(EditAnywhere)
	AQuestActor* PreviousQuest;

	UPROPERTY(EditAnywhere)
	bool bIsTaken = false;

	UPROPERTY(EditAnywhere)
	bool bIsCompleted = false;

	UFUNCTION()
	void TakeQuest(AActor* Character);

	void OnObjectiveCompleted(UObjective* Objective);

	bool IsStoryQuest() const { return bIsStoryQuest; }

	bool IsAvailable();

	FOnQuestObjectiveStatusChanged OnQuestObjectiveStatusChanged;

	FOnQuestStatusChanged OnQuestStatusChanged;

#if WITH_EDITOR

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateLocation();

	UFUNCTION(CallInEditor)
	void AddInteractObjective();

	UFUNCTION(CallInEditor)
	void AddLocationObjective();

	UFUNCTION(CallInEditor)
	void AddCollectionObjective();

#endif

};

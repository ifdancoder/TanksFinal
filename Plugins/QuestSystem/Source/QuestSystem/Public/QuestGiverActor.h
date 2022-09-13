// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "QuestGiverActor.generated.h"

class UQuestDialog;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHasAvailableQuests, bool, HasAvailableQuest);

UCLASS()
class QUESTSYSTEM_API AQuestGiverActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestGiverActor();

	virtual void Serialize(FArchive& Ar) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMeshChar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMeshAvailableQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMeshTakenQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMeshCompletedQuest;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "QuestSystem")
	TSubclassOf<UQuestDialog> QuestDialogClass;

	UFUNCTION(BlueprintCallable)
	void SinusoidMovement(float DeltaSeconds);



	FOnHasAvailableQuests OnHasAvailableQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "QuestSystem")
		float Amplitude = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "QuestSystem")
		float Speed = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* InteractInstigator) override;

	UFUNCTION()
		void SetTickAndVisibility(bool HasAvailableQuest);

	UFUNCTION(BlueprintCallable)
		void HasAvailableQuests();

private:
	float TimeCount;
	float Theta;
	bool bHasAvailableQuest = false;

	UPROPERTY()
		TArray<AActor*> AttachedActors;

	UPROPERTY()
		TMap<FString, AActor*> Quests;
};



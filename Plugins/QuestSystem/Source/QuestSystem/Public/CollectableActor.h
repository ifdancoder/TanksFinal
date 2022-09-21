// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableObject.h"
#include "GameFramework/Actor.h"
#include "CollectableActor.generated.h"

UCLASS()
class QUESTSYSTEM_API ACollectableActor : public AActor, public ICollectableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "ResourceClass")
		TSubclassOf<ACollectableActor> ActorClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnCollectionFinished(AActor* CollectInstigator)
	{
		NotifyCollectFinished(this, CollectInstigator);
	}

	UFUNCTION()
		void OnDestoyingFunc(AActor* Actor);
};




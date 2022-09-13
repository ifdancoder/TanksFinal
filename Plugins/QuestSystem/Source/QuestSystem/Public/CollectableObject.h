// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectableObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCollectableObject : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCollectionFinished, AActor* /*CollectableActor*/, AActor* /*CollectInstigator*/)

class QUESTSYSTEM_API ICollectableObject
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FOnCollectionFinished OnCollectionFinished;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Collect(AActor* CollectInstigator);

	UFUNCTION()
		virtual void Collect_Implementation(AActor* CollectInstigator) {};

	virtual void NotifyCollectFinished(AActor* CollectableActor, AActor* CollectInstigator)
	{
		OnCollectionFinished.Broadcast(CollectableActor, CollectInstigator);
	}
};

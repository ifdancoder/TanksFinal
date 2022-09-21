// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "CollectableObject.h"
#include "InteractableObject.h"
#include "Blueprint/UserWidget.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::UInteractionComponent::OnComponentBeginOverlapFunc);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::UInteractionComponent::OnComponentEndOverlapFunc);
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::OnComponentBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractableObject>())
	{
		ActorToInteract = OtherActor;

		if (InteractMessage == nullptr && InteractMessageWidget)
		{
			InteractMessage = CreateWidget(GetWorld(), InteractMessageWidget);
		}

		if (InteractMessage && !InteractMessage->IsInViewport())
		{
			InteractMessage->AddToViewport();
		}
	}

	else if (OtherActor->Implements<UCollectableObject>())
	{
		ActorToCollect = OtherActor;

		if (CollectMessage == nullptr && CollectMessageWidget)
		{
			CollectMessage = CreateWidget(GetWorld(), CollectMessageWidget);
		}

		if (CollectMessage && !CollectMessage->IsInViewport())
		{
			CollectMessage->AddToViewport();
		}
	}

}

void UInteractionComponent::OnComponentEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == ActorToInteract)
	{
		ActorToInteract = nullptr;

		if (InteractMessage)
		{
			InteractMessage->RemoveFromViewport();
		}
	}

	else if (OtherActor == ActorToCollect)
	{
		ActorToCollect = nullptr;

		if (CollectMessage)
		{
			CollectMessage->RemoveFromViewport();
		}
	}
}

void UInteractionComponent::Interact()
{
	if (ActorToInteract)
	{
		IInteractableObject::Execute_Interact(ActorToInteract, GetOwner());
	}
}

void UInteractionComponent::Collect()
{
	if (ActorToCollect)
	{
		ICollectableObject::Execute_Collect(ActorToCollect, GetOwner());
	}
}

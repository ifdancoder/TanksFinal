// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableActor.h"

#include "NPCEditorSubsystem.h"
#include "ResourcesManagerSubsystem.h"


// Sets default values
ACollectableActor::ACollectableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnDestroyed.AddDynamic(this, &ThisClass::OnDestoyingFunc);

	if (GEditor)
	{
		auto Subsystem = GEditor->GetEditorSubsystem<UNPCEditorSubsystem>();
		if (Subsystem)
		{
			Subsystem->AddResourceActor(this, ActorClass);
		}
	}

}

void ACollectableActor::OnDestoyingFunc(AActor* Actor)
{
	auto ResourcesManager = GetWorld()->GetSubsystem<UResourcesManagerSubsystem>();
	ResourcesManager->RemoveResourceActor(Actor);
}

// Called when the game starts or when spawned
void ACollectableActor::BeginPlay()
{
	Super::BeginPlay();
	auto ResourcesManager = GetWorld()->GetSubsystem<UResourcesManagerSubsystem>();
	ResourcesManager->AddResourceActor(this, ActorClass);

}

// Called every frame
void ACollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


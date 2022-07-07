// Fill out your copyright notice in the Description page of Project Settings.

#include "Chest.h"
#include "InventoryComponent.h"
#include <Components/PrimitiveComponent.h>
#include "InventoryManagerComponent.h"
#include "BasePawn.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
	SetRootComponent(BaseMesh);
}

void AChest::Show(UPrimitiveComponent* pComponent, FKey inKey)
{
	PawnsManager = Cast<ABasePawn>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetInventoryManager();
	PawnsManager->InitChest(LocalInventory);
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	BaseMesh->OnClicked.AddDynamic(this, &AChest::Show);
}


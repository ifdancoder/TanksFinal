// Fill out *your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"
#include "InventoryComponentPlugin.h"
#include "EquipInventoryComponentPlugin.h"
#include "InventoryManagerComponentPlugin.h"
#include "TankPawn.h"

// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
 	LocalInventory = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
    EquipInventory = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
    InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
}

void AInventoryCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GetController() == GetWorld()->GetFirstPlayerController())
    {
		InventoryManager->Init(LocalInventory);
		InventoryManager->InitEquip(EquipInventory);
    }
}

void AInventoryCharacter::EquipItem(EEquipSlot Slot, FName ItemId)
{
    UStaticMeshComponent* Comp = GetEquipComponent(Slot);

    if (Comp)
    {
        auto* Info = InventoryManager->GetItemData(ItemId);
        Comp->SetStaticMesh(Info->Mesh.LoadSynchronous());
        Comp->SetHiddenInGame(false);

        // Armor += Info->Armor;
    }
}

void AInventoryCharacter::UnequipItem(EEquipSlot Slot, FName ItemId)
{
	UStaticMeshComponent* Comp = GetEquipComponent(Slot);

	if (Comp)
	{
		Comp->SetHiddenInGame(true);

        // Armor -= Info->Armor;
	}
}

UStaticMeshComponent* AInventoryCharacter::GetEquipComponent(EEquipSlot EquipSlot)
{
    FName Tag;

    switch (EquipSlot)
    {
        case EEquipSlot::Es_Head:
			Tag = "Head";
			break;
        case EEquipSlot::Es_Body:
            Tag = "Body";
            break;
        case EEquipSlot::Es_Track:
            Tag = "Track";
            break;
        default:
            return nullptr;
    }

    TArray<UActorComponent*> Found = GetComponentsByTag(UStaticMeshComponent::StaticClass(), Tag);

    return Found.IsValidIndex(0) ? Cast<UStaticMeshComponent>(Found[0]) : nullptr;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <Kismet/KismetMathLibrary.h>
#include "Pawns.h"

void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (DraggedText)
	{
		DraggedText->SetText(FText::FromString(DraggedName));
	}
}

void UActorSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->OnMouseButtonUp.AddUObject(this, &ThisClass::OnMouseButtonUp);
}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePosition;
		FVector WorldMouseDirection;

		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		constexpr float Dist = 100000.f;
		GetWorld()->LineTraceSingleByChannel(OutHit, WorldMousePosition, WorldMousePosition + WorldMouseDirection * Dist, ECollisionChannel::ECC_WorldStatic, Params);
	
		if (OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location);
		}
	}
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SpawnedActor = GetWorld()->SpawnActorDeferred<ABasePawn>(SpawnerClass, SpawnTransform, GetWorld()->GetFirstPlayerController()->GetPawn(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	}
	return FReply::Handled();
}

void UActorSpawnerWidget::OnMouseButtonUp()
{
	if (SpawnedActor)
	{
		SpawnedActor->FinishSpawning(SpawnTransform);
		SpawnedActor->SetFriendness(1);
	}
	
	SpawnedActor = nullptr;
}

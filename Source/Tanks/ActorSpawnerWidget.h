// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "TankPlayerController.h"
#include "Turret.h"
#include "ActorSpawnerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UActorSpawnerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasePawn> SpawnerClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWIdget))
	UTextBlock* DraggedText;

	UPROPERTY(EditAnywhere)
	FString DraggedName;

	UPROPERTY()
	ABasePawn* SpawnedActor = nullptr;

	UPROPERTY()
	ATankPlayerController* PlayerController;

	FHitResult OutHit;

	FTransform SpawnTransform = FTransform(FRotator(0, 0, 0), OutHit.Location, FVector(1.f));

	void OnMouseButtonUp();
};

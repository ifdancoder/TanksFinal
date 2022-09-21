// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemCharacter.h"

#include "QuestDialog.h"
#include "QuestList.h"
#include "QuestListComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Sets default values
AQuestSystemCharacter::AQuestSystemCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestListComp = CreateDefaultSubobject<UQuestListComponent>(TEXT("QuestListComponent"));
}

// Called when the game starts or when spawned
void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AQuestSystemCharacter::ToggleQuestListVisibility()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (QuestList)
	{
		QuestList->RemoveFromParent();
		QuestList = nullptr;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		if (QuestListClass)
		{
			QuestList = CreateWidget<UQuestList>(GetWorld(), QuestListClass);
			QuestList->Init(QuestListComp);
			QuestList->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

// Called every frame
void AQuestSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQuestSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestDialog.h"

#include "QuestDescription.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"

void UQuestDialog::NativeConstruct()
{
	Super::NativeConstruct();

	if (AcceptButton)
	{
		AcceptButton->OnReleased.AddDynamic(this, &ThisClass::UQuestDialog::AcceptQuest);
	}

	if (RejectButton)
	{
		RejectButton->OnReleased.AddDynamic(this, &ThisClass::UQuestDialog::RejectQuest);
	}

	auto* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
		PlayerController->SetShowMouseCursor(true);
	}
}

void UQuestDialog::Init(AQuestActor* Quest)
{
	if (Description)
	{
		Description->Init(Quest);
	}
}

void UQuestDialog::AcceptQuest()
{
	OnQuestAccepted.ExecuteIfBound();
	HideDialog();
}

void UQuestDialog::RejectQuest()
{
	HideDialog();
}

void UQuestDialog::HideDialog()
{
	RemoveFromViewport();

	auto* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
	}

	OnQuestQuited.ExecuteIfBound();
}

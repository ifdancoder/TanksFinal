// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "QuestDialog.generated.h"

class AQuestActor;
class UQuestDescription;
class UButton;

UCLASS()
class QUESTSYSTEM_API UQuestDialog : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Init(AQuestActor* Quest);

	FSimpleDelegate OnQuestAccepted;
	FSimpleDelegate OnQuestQuited;

public:
	UPROPERTY(meta = (BindWidgetOptional))
		UQuestDescription* Description;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* AcceptButton;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* RejectButton;

	UFUNCTION()
	void AcceptQuest();

	UFUNCTION()
	void QuickAcceptQuest();

	UFUNCTION()
	void RejectQuest();

	void HideDialog();
};

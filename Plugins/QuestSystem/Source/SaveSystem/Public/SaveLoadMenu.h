// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SaveLoadMenu.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class SAVESYSTEM_API USaveLoadMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* SlotName;

	UPROPERTY(meta=(BindWidget))
	UButton* SaveBtn;

	UPROPERTY(meta=(BindWidget))
	UButton* LoadBtn;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SaveFunc();

	UFUNCTION()
	void LoadFunc();
};

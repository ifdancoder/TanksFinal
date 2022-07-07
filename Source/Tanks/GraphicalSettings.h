// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/Slider.h>
#include "RadioButtons.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "GraphicalSettings.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UGraphicalSettings : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* SaveButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UTextBlock* Status;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UImage* BackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* BlackWhiteButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* OrdinaryButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class USlider* Slider;

	UFUNCTION()
	void SaveClicked();

	UFUNCTION()
	void OrdinaryClicked();

	UFUNCTION()
	void BlackWhiteClicked();

	UFUNCTION()
	void SetStatus();

	UFUNCTION()
	void BackClicked();
};

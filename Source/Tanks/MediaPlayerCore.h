// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaPlayerCore.generated.h"

/**
 * 
 */

class UButton;
class UMediaPlayer;

UCLASS()
class TANKS_API UMediaPlayerCore : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnStopClicked();

	UFUNCTION()
	void OnBrowseClicked();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* OutputImage;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere)
	UMediaPlayer* MediaPlayer;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* Play;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* Stop;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* Browse;

	UFUNCTION(BlueprintCallable)
	int IsVideo();

	bool bIsVideo = false;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class QUESTEDITOR_API SColorComboBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SColorComboBox)
		{
		}

	SLATE_END_ARGS()

	//TSharedPtr<FColor> FComboItemType;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedRef<SWidget> MakeWidgetForOption(TSharedPtr<FColor> InOption);
	void OnSelectionChanged(TSharedPtr<FColor> NewValue, ESelectInfo::Type);
	FText GetCurrentItemLabel() const;
	FString GetColorName(TSharedPtr<FColor> Color) const;

	TSharedPtr<FColor> CurrentItem;
	TArray<TSharedPtr<FColor>> Options;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "SColorComboBox.h"

#include "EditorModeManager.h"
#include "QuestEditorEdMode.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SColorComboBox::Construct(const FArguments& InArgs)
{
	Options.Add(MakeShareable(new FColor(FColor::Black)));
	Options.Add(MakeShareable(new FColor(FColor::Blue)));
	Options.Add(MakeShareable(new FColor(FColor::Red)));
	Options.Add(MakeShareable(new FColor(FColor::Yellow)));
	Options.Add(MakeShareable(new FColor(FColor::Green)));
	Options.Add(MakeShareable(new FColor(FColor::Orange)));
	Options.Add(MakeShareable(new FColor(FColor::Purple)));
	Options.Add(MakeShareable(new FColor(FColor::Cyan)));
	Options.Add(MakeShareable(new FColor(FColor::Emerald)));
	Options.Add(MakeShareable(new FColor(FColor::White)));
	
	
	CurrentItem = Options[0];

	const auto EditorMode = GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId);
	EditorMode->BaseBoxColor = *CurrentItem;
 
	ChildSlot
		[
			SNew(SComboBox<TSharedPtr<FColor>>)
			.OptionsSource(&Options)
			.OnSelectionChanged(this, &SColorComboBox::OnSelectionChanged)
			.OnGenerateWidget(this, &SColorComboBox::MakeWidgetForOption)
			.InitiallySelectedItem(CurrentItem)
			[
				SNew(STextBlock)
				.Text(this, &SColorComboBox::GetCurrentItemLabel)
			]
		];
}

TSharedRef<SWidget> SColorComboBox::MakeWidgetForOption(TSharedPtr<FColor> InOption)
{
	return SNew(STextBlock).Text(FText::FromString(GetColorName(InOption)));
}

void SColorComboBox::OnSelectionChanged(TSharedPtr<FColor> NewValue, ESelectInfo::Type)
{
	CurrentItem = NewValue;
	auto EditorMode = GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId);
	EditorMode->BaseBoxColor = *CurrentItem;
}

FText SColorComboBox::GetCurrentItemLabel() const
{
	if (CurrentItem.IsValid())
	{
		return FText::FromString(GetColorName(CurrentItem));
	}
 
	return FText::FromString("InvalidComboEntryText");
}

FString SColorComboBox::GetColorName(TSharedPtr<FColor> Color) const
{
	FString ColorName;
	if (*Color == FColor::Black)
	{
		ColorName = "Black";
	}
	else if (*Color == FColor::Blue)
	{
		ColorName = "Blue";
	}
	else if (*Color == FColor::Yellow)
	{
		ColorName = "Yellow";
	}
	else if (*Color == FColor::Red)
	{
		ColorName = "Red";
	}
	else if (*Color == FColor::Orange)
	{
		ColorName = "Orange";
	}
	else if (*Color == FColor::Purple)
	{
		ColorName = "Purple";
	}
	else if (*Color == FColor::Emerald)
	{
		ColorName = "Emerald";
	}
	else if (*Color == FColor::Cyan)
	{
		ColorName = "Cyan";
	}
	else if (*Color == FColor::White)
	{
		ColorName = "White";
	}
	else if (*Color == FColor::Green)
	{
		ColorName = "Green";
	}
	else
	{
		ColorName = "InvalidName";
	}
	return ColorName;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

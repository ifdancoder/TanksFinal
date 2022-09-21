// Fill out your copyright notice in the Description page of Project Settings.


#include "StandaloneWindowEditorTool/Public/SQuestListWidget.h"

#include "ISinglePropertyView.h"
#include "Quest.h"
#include "Engine/Selection.h"

void SQuestList::Construct(const SQuestList::FArguments& InArgs)
{
	ChildSlot
		.Padding(FMargin(8))
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
		.MaxHeight(24.f)
		[
			SNew(SButton)
			.Text(FText::FromString("Show All Quests"))
		.OnClicked(this, &SQuestList::OnButtonPressed)
		]

	+ SVerticalBox::Slot()
		[
			SAssignNew(QuestListView, SQuestListView)
			.ItemHeight(24)
		.ListItemsSource(&QuestListItems)
		.OnGenerateRow(this, &SQuestList::OnGenerateWidgetForModuleListView)
		.HeaderRow
		(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("QuestName")
			.DefaultLabel(NSLOCTEXT("QuestList", "QuestName", "Quest Name"))
			.HeaderContentPadding(FMargin(2.f))
			+ SHeaderRow::Column("QuestDescription")
			.DefaultLabel(NSLOCTEXT("QuestList", "QuestDescription", "Quest Description"))
			.HeaderContentPadding(FMargin(2.f))
			+ SHeaderRow::Column("StoryQuest")
			.DefaultLabel(NSLOCTEXT("QuestList", "StoryQuest", "Story Quest"))
			.HeaderContentPadding(FMargin(2.f))
			+ SHeaderRow::Column("KeepObjectivesOrder")
			.DefaultLabel(NSLOCTEXT("QuestList", "KeepObjectivesOrder", "Keep Objectives Order"))
			.HeaderContentPadding(FMargin(2.f))
			+ SHeaderRow::Column("PreviousQuest")
			.DefaultLabel(NSLOCTEXT("QuestList", "PreviousQuest", "PreviousQuest"))
			.HeaderContentPadding(FMargin(2.f))
			+ SHeaderRow::Column("Objectives")
			.DefaultLabel(NSLOCTEXT("QuestList", "Objectives", "Objectives"))
			.HeaderContentPadding(FMargin(2.f))
		)
		]
		];

	// Register to find out about module changes
	FModuleManager::Get().OnModulesChanged().AddSP(this, &SQuestList::OnModulesChanged);


	// Gather data from module manager
	UpdateModuleListItems();
}


SQuestList::~SQuestList()
{
	// Unregister callbacks
	FModuleManager::Get().OnModulesChanged().RemoveAll(this);
}

void SQuestList::OnFilterTextChanged(const FText& InFilterText)
{
	UpdateModuleListItems();
}

FReply SQuestList::OnButtonPressed()
{
	TArray<AQuestActor*> QuestsArray;
	if (GEditor)
	{
		for (auto Iter = GEditor->GetSelectedActorIterator(); Iter; ++Iter)
		{
			if (auto Quest = Cast<AQuestActor>(*Iter))
			{
				QuestsArray.Add(Quest);
			}
		}
	}
	GEditor->SelectNone(true, true);
	QuestListItems.Reset();
	for (int32 i = 0; i < QuestsArray.Num(); ++i)
	{
		GEditor->SelectActor(QuestsArray[i], true, true);
		TSharedPtr<FQuestListItem> Item = MakeShareable(new FQuestListItem);
		Item->QuestName = QuestsArray[i]->Name;
		Item->QuestDescription = QuestsArray[i]->Description;
		Item->bIsStoryQuest = QuestsArray[i]->bIsStoryQuest;
		Item->bKeepObjectivesOrder = QuestsArray[i]->bKeepObjectivesOrder;
		Item->PreviousQuest = QuestsArray[i]->PreviousQuest;
		Item->QuestPtr = QuestsArray[i];

		QuestListItems.Add(Item);
	}
	QuestListView->RequestListRefresh();
	return FReply::Handled();
}

TSharedRef<ITableRow> SQuestList::OnGenerateWidgetForModuleListView(TSharedPtr< FQuestListItem > InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
#define LOCTEXT_NAMESPACE "QuestList"

	class SQuestItemWidget : public SMultiColumnTableRow< TSharedPtr< FQuestListItem > >
	{
	public:
		SLATE_BEGIN_ARGS(SQuestItemWidget) {}
		SLATE_END_ARGS()

			TSharedPtr< FQuestListItem > Item;

		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FQuestListItem> InListItem)
		{
			Item = InListItem;

			SMultiColumnTableRow< TSharedPtr< FQuestListItem > >::Construct(FSuperRowType::FArguments(), InOwnerTable);
		}

		FReply EditButtonPressed(AQuestActor* Quest)
		{
			FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			FSinglePropertyParams Params;
			auto a = PropertyModule.CreateSingleProperty(Quest, "Name", Params);


			return FReply::Handled();
		}

		TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName)
		{
			FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			FSinglePropertyParams Params;


			if (ColumnName == "QuestName")
			{
				auto NamePropertyWidget = PropertyModule.CreateSingleProperty(Item->QuestPtr, "Name", Params);
				return
					// SNew( STextBlock )
					// .Text( Item->QuestName)
					// .Margin(1.f);
					NamePropertyWidget->AsShared();
			}
			else if (ColumnName == "QuestDescription")
			{
				auto DescriptionPropertyWidget = PropertyModule.CreateSingleProperty(Item->QuestPtr, "Description", Params);
				return
					// SNew( STextBlock )
					// //.Text(Item->QuestDescription)
					// .Margin(1.f)
					// .Text(Item->QuestDescription)
					// .AutoWrapText(true);
					DescriptionPropertyWidget->AsShared();
			}
			else if (ColumnName == "StoryQuest")
			{
				auto IsStoryQuestPropertyWidget = PropertyModule.CreateSingleProperty(Item->QuestPtr, "bIsStoryQuest", Params);
				return
					// SNew(SCheckBox)
					// .Padding(1.f)
					// .IsChecked_Lambda([this]()
					// {
					// 	return Item->bIsStoryQuest ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
					// });
					IsStoryQuestPropertyWidget->AsShared();
			}
			else if (ColumnName == "KeepObjectivesOrder")
			{
				auto KeepObjectivesOrderPropertyWidget = PropertyModule.CreateSingleProperty(Item->QuestPtr, "bKeepObjectivesOrder", Params);
				return
					// SNew(SCheckBox)
					// .Padding(1.f)
					// .IsChecked_Lambda([this]()
					// {
					// 	return Item->bKeepObjectivesOrder ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
					// });
					KeepObjectivesOrderPropertyWidget->AsShared();
			}
			else if (ColumnName == "PreviousQuest")
			{
				// if (Item->PreviousQuest)
				// {
				// 	return
				// 	SNew(STextBlock)
				// 	.Margin(1.f)
				// 	.Text(Item->PreviousQuest->Name);
				// }
				// else
				// {
				// 	return
				// 	SNew(STextBlock)
				// 	.Margin(1.f)
				// 	.Text(FText::FromString("None"));
				// }
				auto PreviousQuestPropertyWidget = PropertyModule.CreateSingleProperty(Item->QuestPtr, "PreviousQuest", Params);
				return
					PreviousQuestPropertyWidget->AsShared();
			}
			else if (ColumnName == "Objectives")
			{
				auto ObjectivesPropertyWidget = PropertyModule.CreateSingleProperty(Item->QuestPtr, "Objectives", Params);
				return
					// SNew(SButton)
					// .ContentPadding(1.f)
					// .Text(FText::FromString("Edit"))
					// .OnClicked(this, &SQuestItemWidget::EditButtonPressed, Item->QuestPtr);
					ObjectivesPropertyWidget->AsShared();
			}

			else
			{
				return SNew(STextBlock).Text(LOCTEXT("UnknownColumn", "Unknown Column"));
			}

		}


	};

	return SNew(SQuestItemWidget, OwnerTable, InItem);

#undef LOCTEXT_NAMESPACE
}

void SQuestList::OnModulesChanged(FName ModuleThatChanged, EModuleChangeReason ReasonForChange)
{
	// @todo: Consider using dirty bit for this instead, refresh on demand
	UpdateModuleListItems();
}

void SQuestList::UpdateModuleListItems()
{
	QuestListItems.Reset();

	// Update the list view if we have one
	if (QuestListView.IsValid())
	{
		QuestListView->RequestListRefresh();
	}
}



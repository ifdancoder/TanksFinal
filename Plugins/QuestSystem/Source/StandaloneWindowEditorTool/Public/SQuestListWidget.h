// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Objective.h"
//#include "QuestList.generated.h"

/**
 *
 */

class AQuestActor;

class SQuestList : public SCompoundWidget
{
public:

    SLATE_BEGIN_ARGS(SQuestList) {}
    SLATE_END_ARGS()

        /**
             * Constructs this widget
             *
             * @param InArgs    Declaration from which to construct the widget
             */
        void Construct(const FArguments& InArgs);

    /** SModuleUI destructor */
    ~SQuestList();

private:
    struct FQuestListItem
    {
        FText QuestName;
        FText QuestDescription;
        bool bIsStoryQuest;
        bool bKeepObjectivesOrder;
        AQuestActor* PreviousQuest;
        AQuestActor* QuestPtr;
    };

    TSharedRef<ITableRow> OnGenerateWidgetForModuleListView(TSharedPtr< FQuestListItem > InItem, const TSharedRef<STableViewBase>& OwnerTable);


    void OnModulesChanged(FName ModuleThatChanged, EModuleChangeReason ReasonForChange);


    void UpdateModuleListItems();


    void OnFilterTextChanged(const FText& InFilterText);

    FReply OnButtonPressed();
    TArray<AQuestActor*> Quests;




private:

    typedef SListView< TSharedPtr< FQuestListItem > > SQuestListView;
    typedef TArray< TSharedPtr< FQuestListItem > > FQuestArray;

    /** List items for the module list */
    TArray< TSharedPtr< FQuestListItem > > QuestListItems;

    /** List of all known modules */
    TSharedPtr< SQuestListView > QuestListView;
};
// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditorEdModeToolkit.h"

#include "QuestEditorEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "EditorModeManager.h"
#include "NPCEditorSubsystem.h"
#include "Objective.h"
#include "Quest.h"
#include "QuestGiverActor.h"
#include "SColorComboBox.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "FQuestEditorModeEdModeToolkit"

FQuestEditorModeEdModeToolkit::FQuestEditorModeEdModeToolkit()
{
}

void FQuestEditorModeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}
		
	};
	

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		//.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.MaxHeight(24)
			[
				SNew(SButton)
				.Text(FText::FromString("Select All NPC's"))
				.OnClicked_Lambda([]()
				{
					if (GEngine && GEditor)
					{
						TArray<AQuestGiverActor*> QuestGiversArray;
						for	(auto Iter = GEditor->GetSelectedActorIterator(); Iter; ++Iter)
						{
							if (auto QuestGiver = Cast<AQuestGiverActor>(*Iter))
							{
								QuestGiversArray.Add(QuestGiver);
							}
						}
						GEditor->SelectNone(true, true);
						if (QuestGiversArray.Num() == 0)
						{
							auto Subsystem  = GEditor->GetEditorSubsystem<UNPCEditorSubsystem>();
							if (Subsystem)
							{
								QuestGiversArray =  Subsystem->GetQuestGiverActors();
							}
							for (auto QuestGiver : QuestGiversArray)
							{
								GEditor->SelectActor(QuestGiver, true, true);
							}
						}
						else
						{
							TArray<AActor*>QuestObjectivesArray; 
							TArray<AActor*>QuestsArray;
							for (auto QuestGiver : QuestGiversArray)
							{
								QuestGiver->GetAttachedActors(QuestsArray);
								for (auto Actor : QuestsArray)
								{
									if (auto Quest = Cast<AQuestActor>(Actor) )
									{
										auto Objectives = Quest->GetObjectives();
										for	(auto Objective : Objectives)
										{
											if (auto InteractionObjective = Cast<UInteractionObjective>(Objective))
											{
												QuestObjectivesArray.Add(InteractionObjective->Target);
											}
											else if (auto LocationObjective = Cast<ULocationObjective>(Objective))
											{
												QuestObjectivesArray.Add(LocationObjective->Marker);
											}
											else if (auto CollectionObjective = Cast<UCollectionObjective>(Objective))
											{
												auto Subsystem  = GEditor->GetEditorSubsystem<UNPCEditorSubsystem>();
												if (Subsystem)
												{
													//Subsystem->FindActorsOfClass(CollectionObjective->GetClass());
													for (auto CollectableActor : Subsystem->FindActorsOfClass(CollectionObjective->GetClass()))
													{
														QuestObjectivesArray.Add(CollectableActor);
													}
												}
											}
										}

										GEditor->SelectActor(Quest, true, true);
									}
								}
							}

							for (auto QuestObjective : QuestObjectivesArray)
							{
								GEditor->SelectActor(QuestObjective, true, true);
							}
						}
						
					}
					return FReply::Handled();
				})

				
			]
			+SVerticalBox::Slot()
			.MaxHeight(24)
			[
				SNew(SColorComboBox)
			]
	
		];	
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FQuestEditorModeEdModeToolkit::GetToolkitFName() const
{
	return FName("QuestEditorModeEdMode");
}

FText FQuestEditorModeEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("QuestEditorModeEdModeToolkit", "DisplayName", "QuestEditorModeEdMode Tool");
}

class FEdMode* FQuestEditorModeEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE

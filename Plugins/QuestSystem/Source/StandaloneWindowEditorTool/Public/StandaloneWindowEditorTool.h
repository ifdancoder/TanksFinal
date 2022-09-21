// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


class FToolBarBuilder;
class FMenuBuilder;
class AQuestActor;

class FStandaloneWindowEditorToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<FUICommandList> CommandList;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();



	/* The list of strings */
	TArray<AQuestActor*> Items;

	/* The actual UI list */
	TSharedPtr< SListView< AQuestActor* > > ListViewWidget;

	//TSharedRef<class SQuestList> QuestList;
	
	void RegisterMenus();

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;


};

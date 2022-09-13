// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowEditorTool.h"

#include "StandaloneWindowEditorToolStyle.h"
#include "StandaloneWindowEditorToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "SQuestListWidget.h"
#include "Widgets/Layout/SHeader.h"

static const FName StandaloneWindowEditorToolTabName("StandaloneWindowEditorTool");

#define LOCTEXT_NAMESPACE "FStandaloneWindowEditorToolModule"

void FStandaloneWindowEditorToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FStandaloneWindowEditorToolStyle::Initialize();
	FStandaloneWindowEditorToolStyle::ReloadTextures();

	FStandaloneWindowEditorToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowEditorToolModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneWindowEditorToolModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowEditorToolTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowEditorToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowEditorToolTabTitle", "QuestEditorTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// {
	// 	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	// 	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
	// 		FMenuExtensionDelegate::CreateRaw(this, &FStandaloneWindowEditorToolModule::AddMenuExtension));
	//
	// 	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	// }
	
	// {
	// 	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender());
	// 	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
	// 		FToolBarExtensionDelegate::CreateRaw(this, &FStandaloneWindowEditorToolModule::AddToolbarExtension));
	//
	// 	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	// }
}

void FStandaloneWindowEditorToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneWindowEditorToolStyle::Shutdown();

	FStandaloneWindowEditorToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowEditorToolTabName);
}


TSharedRef<SDockTab> FStandaloneWindowEditorToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SQuestList)
		];
}

void FStandaloneWindowEditorToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneWindowEditorToolTabName);
}

void FStandaloneWindowEditorToolModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FStandaloneWindowEditorToolModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow);
}

void FStandaloneWindowEditorToolModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FStandaloneWindowEditorToolCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowEditorToolModule, StandaloneWindowEditorTool)
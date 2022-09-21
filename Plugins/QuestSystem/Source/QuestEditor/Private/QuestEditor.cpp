// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditor.h"
#include "QuestEditorEdMode.h"

#define LOCTEXT_NAMESPACE "FQuestEditorModeModule"

void FQuestEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FQuestEditorModeEdMode>(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId, LOCTEXT("QuestEditorModeEdModeName", "QuestEditorModeEdMode"), FSlateIcon(), true);
}

void FQuestEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestEditorModeModule, QuestEditorMode)
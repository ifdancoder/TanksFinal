// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowEditorToolCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneWindowEditorToolModule"

void FStandaloneWindowEditorToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "QuestEditorTool", "Bring up QuestEditorTool window", EUserInterfaceActionType::Button, FInputChord() /*FInputGesture() Depricated*/);
}

#undef LOCTEXT_NAMESPACE

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StandaloneWindowEditorToolStyle.h"

class FStandaloneWindowEditorToolCommands : public TCommands<FStandaloneWindowEditorToolCommands>
{
public:

	FStandaloneWindowEditorToolCommands()
		: TCommands<FStandaloneWindowEditorToolCommands>(TEXT("StandaloneWindowEditorTool"),
			NSLOCTEXT("Contexts", "StandaloneWindowEditorTool", "StandaloneWindowEditorTool Plugin"),
			NAME_None, FStandaloneWindowEditorToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
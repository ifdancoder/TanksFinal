// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditorEdMode.h"
#include "QuestEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "Engine/Font.h"
#include "Engine/Selection.h"

const FEditorModeID FQuestEditorModeEdMode::EM_QuestEditorModeEdModeId = TEXT("EM_QuestEditorModeEdMode");

FQuestEditorModeEdMode::FQuestEditorModeEdMode()
{

}

FQuestEditorModeEdMode::~FQuestEditorModeEdMode()
{

}

void FQuestEditorModeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FQuestEditorModeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}

	UpdateSelectedActors();
}

void FQuestEditorModeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

void FQuestEditorModeEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	for (AActor* BoundedActor : SelectedActors)
	{
		DrawWireBox(
		PDI,
		BoundedActor->GetComponentsBoundingBox(true),
		BaseBoxColor,
		1
		);
	}
}

void FQuestEditorModeEdMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View,
	FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	for (AActor* SelectedActor : SelectedActors)
	{
		if (Canvas)
		{
			FBox Bounds = SelectedActor->GetComponentsBoundingBox(true);

			FVector DrawPos = Bounds.GetCenter() + FVector(0.f,0.f, Bounds.GetExtent().Z);
			FVector2D PixelLocation;
			View->ScreenToPixel(View->WorldToScreen(DrawPos), PixelLocation);
			PixelLocation /= ViewportClient->GetDPIScale();
			UFont* RenderFont = GEngine->GetSmallFont();
			Canvas->DrawShadowedText(PixelLocation.X, PixelLocation.Y, FText::FromString(SelectedActor->GetName()), RenderFont, FLinearColor::Black);
		}
	}
}

void FQuestEditorModeEdMode::ActorSelectionChangeNotify()
{
	FEdMode::ActorSelectionChangeNotify();

	UpdateSelectedActors();
}

bool FQuestEditorModeEdMode::UsesToolkits() const
{
	return true;
}

void FQuestEditorModeEdMode::UpdateSelectedActors()
{
	SelectedActors.Empty();

	if (GEditor)
	{
		USelection* ActorsSelection = GEditor->GetSelectedActors();

		for (FSelectionIterator Iter(*ActorsSelection); Iter; ++Iter)
		{
			AActor* LevelActor = Cast<AActor>(*Iter);
			if (LevelActor && !SelectedActors.Contains(LevelActor))
			{
				SelectedActors.Add(LevelActor);
			}
		}
	}
	
}





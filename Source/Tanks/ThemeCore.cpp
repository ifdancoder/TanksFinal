// Fill out your copyright notice in the Description page of Project Settings.


#include "ThemeCore.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"
#include <UObject/NoExportTypes.h>
#include <Templates/SharedPointer.h>
#include <Brushes/SlateImageBrush.h>
#include <Styling/SlateStyle.h>

ThemeCore::ThemeCore()
{
}

ThemeCore::~ThemeCore()
{
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> ThemeCore::StylePtr;

TSharedPtr<ISlateStyle> ThemeCore::FindStyle()
{
	FString Path = FPaths::ProjectContentDir() / TEXT("/UI");
	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MyCoreStyle"), Path, Path);

	Style->Set("Red", FLinearColor::Red);
	Style->Set("DefaultPadding", FMargin(5.f));
	Style->Set("Frog", new IMAGE_BRUSH("frog", FVector2D(256.f)));

	return Style;
}

#undef IMAGE_BRUSH

void ThemeCore::Initialize()
{
	Shutdown();

	StylePtr = FindStyle();

	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void ThemeCore::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		StylePtr.Reset();
	}
}

const ISlateStyle& ThemeCore::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}
	return *StylePtr;
}

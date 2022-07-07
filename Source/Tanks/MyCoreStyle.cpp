// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCoreStyle.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"
#include <UObject/NoExportTypes.h>
#include <Templates/SharedPointer.h>
#include <Brushes/SlateImageBrush.h>
#include <Styling/SlateStyle.h>

int MyCoreStyle::CurrentStyle;
TSharedPtr<ISlateStyle> MyCoreStyle::StylePtr;

MyCoreStyle::MyCoreStyle()
{
	CurrentStyle = 0;
}

MyCoreStyle::~MyCoreStyle()
{
}

//#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
//
//TSharedPtr<ISlateStyle> MyCoreStyle::StylePtr;
//
//TSharedPtr<ISlateStyle> MyCoreStyle::FindStyle()
//{
//	FString Path = FPaths::ProjectContentDir() / TEXT("/UI");
//	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MyCoreStyle"), Path, Path);
//
//	Style->Set("Red", FLinearColor::Red);
//	Style->Set("DefaultPadding", FMargin(5.f));
//	Style->Set("Frog", new IMAGE_BRUSH("frog", FVector2D(256.f)));
//
//	return Style;
//}
//
//#undef IMAGE_BRUSH

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> MyCoreStyle::FindStyle(int InStyle)
{
	FString Path = FPaths::ProjectContentDir() / TEXT("/UI");
	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MyCoreStyle"), Path, Path);

	if (!InStyle)
	{
		Style->Set("Background", FLinearColor::Yellow);
		Style->Set("PlayerImage", new IMAGE_BRUSH("OrdinaryPlayerImage", FVector2D(64.f)));
		Style->Set("BordersImage", new IMAGE_BRUSH("OrdinaryBordersImage", FVector2D(256.f)));
	}
	else
	{
		Style->Set("Background", FLinearColor::Gray);
		Style->Set("PlayerImage", new IMAGE_BRUSH("BlackWhitePlayerImage", FVector2D(64.f)));
		Style->Set("BordersImage", new IMAGE_BRUSH("BlackWhiteBordersImage", FVector2D(256.f)));
	}
	return Style;
}

#undef IMAGE_BRUSH

void MyCoreStyle::Initialize(int InStyle)
{
	Shutdown();
	
	StylePtr = FindStyle(InStyle);

	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void MyCoreStyle::ChangeStyle(int InStyle)
{
	CurrentStyle = InStyle;
	Initialize(InStyle);
}

int MyCoreStyle::GetStatus()
{
	return CurrentStyle;
}

void MyCoreStyle::Shutdown()
{
	if(StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		StylePtr.Reset();
	}
}

const ISlateStyle& MyCoreStyle::Get()
{
	Initialize(CurrentStyle);
	return *StylePtr;
}

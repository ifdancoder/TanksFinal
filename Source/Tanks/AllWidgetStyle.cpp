// Fill out your copyright notice in the Description page of Project Settings.


#include "AllWidgetStyle.h"
#include "MyCoreStyle.h"

FAllStyle::FAllStyle()
{
}

FAllStyle::~FAllStyle()
{
}

const FName FAllStyle::TypeName(TEXT("FAllStyle"));

const FAllStyle& FAllStyle::GetDefault()
{
	static FAllStyle Default;
	return Default;
}

void FAllStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	FSlateWidgetStyle::GetResources(OutBrushes);

	HeaderTextStyle.GetResources(OutBrushes);
	TextStyle.GetResources(OutBrushes);
}
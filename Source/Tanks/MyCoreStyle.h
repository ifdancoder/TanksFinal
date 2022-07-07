// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"

/**
 * 
 */
class TANKS_API MyCoreStyle
{
public:

	MyCoreStyle();
	~MyCoreStyle();

	static TSharedPtr<ISlateStyle> FindStyle(int InStyle);

	static void Initialize(int InStyle);

	static void ChangeStyle(int InStyle);

	static int GetStatus();

	static void Shutdown();

	static const ISlateStyle& Get();

private:
	
	static int CurrentStyle;
	
	static TSharedPtr<ISlateStyle> StylePtr;
};

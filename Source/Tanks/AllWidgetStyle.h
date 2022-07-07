// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "AllWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct TANKS_API FAllStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FAllStyle();
	virtual ~FAllStyle();

	UPROPERTY(EditAnywhere, Category = Appereance)
	FTextBlockStyle HeaderTextStyle;

	UPROPERTY(EditAnywhere, Category = Appereance)
	FTextBlockStyle TextStyle;

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FAllStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UAllWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FAllStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};

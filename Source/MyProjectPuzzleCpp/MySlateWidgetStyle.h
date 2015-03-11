// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Slate.h"
#include "SlateCore.h"
#include "SlateWidgetStyleContainerBase.h"
#include "MySlateWidgetStyle.generated.h"


/**
 * 
 */
USTRUCT()
struct MYPROJECTPUZZLECPP_API FMySlateStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

public:
	/**
	 * The brush used to draw the defeat image
	 */	
	UPROPERTY(EditAnywhere, Category=Appearance)
	FSlateBrush DefeatImage;
	FMySlateStyle& SetDefeatImage(const FSlateBrush& InDefeatImage) { DefeatImage = InDefeatImage; return *this; }


	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FMySlateStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UMySlateWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FMySlateStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};

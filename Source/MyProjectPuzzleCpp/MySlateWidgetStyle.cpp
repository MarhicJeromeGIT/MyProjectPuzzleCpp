// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectPuzzleCpp.h"
#include "MySlateWidgetStyle.h"



const FName FMySlateStyle::TypeName(TEXT("FMySlateStyle"));

const FMySlateStyle& FMySlateStyle::GetDefault()
{
	static FMySlateStyle Default;
	return Default;
}

void FMySlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
	OutBrushes.Add(&DefeatImage);
}


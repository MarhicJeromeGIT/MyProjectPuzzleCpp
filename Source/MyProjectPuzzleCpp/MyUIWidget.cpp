//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyUIWidget.cpp
 
#include "MyProjectPuzzleCpp.h"
#include "MyUIWidget.h"
 
void SMyUIWidget::Construct(const FArguments& InArgs)
{
	//HUDStyle = &FStrategyStyle::Get().GetWidgetStyle<FStrategyHUDStyle>("DefaultStrategyHUDStyle");

	OwnerHUD = InArgs._OwnerHUD;
 
	////////////////////////////////////////////////////////////////////////////////////////////////////
        /////If the code below doesn't look like C++ to you it's because it (sort-of) isn't,
        /////Slate makes extensive use of the C++ Prerocessor(macros) and operator overloading,
        /////Epic is trying to make our lives easier, look-up the macro/operator definitions to see why.
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				//SNew(SImage)
				//.Image(this, &DefeatImage)
				//.Visibility(this, &SStrategySlateHUDWidget::GetResultScreenVisibility)

				SNew(STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::White)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo("Veranda", 16))
				.Text(FText::FromString("Hello, Slate!"))
			]
		];
}


const FSlateBrush* SMyUIWidget::GetGameResultImage() const
{
	return NULL;
	//return &HUDStyle->DefeatImage;
}
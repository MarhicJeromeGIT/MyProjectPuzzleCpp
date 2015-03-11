// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectPuzzleCpp.h"
#include "MyUIWidget.h"
#include "MyHUD.h"
#include "Engine.h"

void AMyHUD::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
        /////So far only TSharedPtr<SMyUIWidget> has been created, now create the actual object.
	/////Create a SMyUIWidget on heap, our MyUIWidget shared pointer provides handle to object
        /////Widget will not self-destruct unless the HUD's SharedPtr (and all other SharedPtrs) destruct first.
	SAssignNew(MyUIWidget, SMyUIWidget).OwnerHUD(this);
 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pass our viewport a weak ptr to our widget
	if (GEngine->IsValidLowLevel())
        {
		GEngine->GameViewport->
                /*Viewport's weak ptr will not give Viewport ownership of Widget*/
		AddViewportWidgetContent( SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()) );
        }
 
	if (MyUIWidget.IsValid())
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/////Set widget's properties as visible (sets child widget's properties recursively)
		MyUIWidget->SetVisibility(EVisibility::Visible);
	}
}
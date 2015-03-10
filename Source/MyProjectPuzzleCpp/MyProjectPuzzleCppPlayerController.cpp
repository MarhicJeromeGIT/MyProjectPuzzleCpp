// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPuzzleCpp.h"
#include "MyProjectPuzzleCppPlayerController.h"

AMyProjectPuzzleCppPlayerController::AMyProjectPuzzleCppPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

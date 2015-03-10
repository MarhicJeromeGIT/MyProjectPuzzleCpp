// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPuzzleCpp.h"
#include "MyProjectPuzzleCppGameMode.h"
#include "MyProjectPuzzleCppPlayerController.h"
#include "MyHUD.h"

AMyProjectPuzzleCppGameMode::AMyProjectPuzzleCppGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = AMyProjectPuzzleCppPlayerController::StaticClass();

	HUDClass = AMyHUD::StaticClass();
}

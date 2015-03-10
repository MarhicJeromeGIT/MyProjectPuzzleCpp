// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "MyProjectPuzzleCppPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AMyProjectPuzzleCppPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyProjectPuzzleCppPlayerController(const FObjectInitializer& ObjectInitializer);
};



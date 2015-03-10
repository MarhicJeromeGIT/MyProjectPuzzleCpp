// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "MyProjectPuzzleCppGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AMyProjectPuzzleCppGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMyProjectPuzzleCppGameMode(const FObjectInitializer& ObjectInitializer);
};




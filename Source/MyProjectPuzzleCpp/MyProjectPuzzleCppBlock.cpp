// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPuzzleCpp.h"
#include "MyProjectPuzzleCppBlock.h"
#include "MyProjectPuzzleCppBlockGrid.h"

AMyProjectPuzzleCppBlock::AMyProjectPuzzleCppBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BlueMaterial(TEXT("/Engine/TemplateResources/MI_Template_BaseBlue.MI_Template_BaseBlue"))
			, OrangeMaterial(TEXT("/Engine/TemplateResources/MI_Template_BaseOrange.MI_Template_BaseOrange"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.1,0.1,0.1));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->AttachTo(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AMyProjectPuzzleCppBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AMyProjectPuzzleCppBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
}

void AMyProjectPuzzleCppBlock::BlockClicked(UPrimitiveComponent* ClickedComp)
{
	// Check we are not already active
	if(!bIsActive)
	{
		bIsActive = true;

		// Change material
		BlockMesh->SetMaterial(0, OrangeMaterial);

		// Tell the Grid
		if(OwningGrid != NULL)
		{
			OwningGrid->AddScore();
		}

		// Make the move :
		OwningGrid->makeMove(this);

		
	}
}


void AMyProjectPuzzleCppBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	BlockClicked(TouchedComponent);
}


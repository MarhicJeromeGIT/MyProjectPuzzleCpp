// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectPuzzleCpp.h"
#include "ChessPiece.h"
#include "MyProjectPuzzleCppBlockGrid.h"

// Sets default values
AChessPiece::AChessPiece(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isSelectable = false;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
	//		, BlueMaterial(TEXT("/Engine/TemplateResources/MI_Template_BaseBlue.MI_Template_BaseBlue"))
			, BlueMaterial(TEXT("Material'/Game/Puzzle/Materials/MaterialChessboard.MaterialChessboard'"))
			, OrangeMaterial(TEXT("/Engine/TemplateResources/MI_Template_BaseOrange.MI_Template_BaseOrange"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
//	PieceMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	PieceMesh->SetRelativeScale3D(FVector(0.5,0.5,0.5));
	PieceMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	PieceMesh->AttachTo(DummyRoot);
	PieceMesh->OnClicked.AddDynamic(this, &AChessPiece::PieceClicked);
	PieceMesh->OnInputTouchBegin.AddDynamic(this, &AChessPiece::OnFingerPressedBlock);

	MaterialWhite   = NULL;
	MaterialBlack   = NULL;
	MaterialGlowing = NULL;
	static ConstructorHelpers::FObjectFinder<UMaterial> FindWhiteMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Pine.M_Wood_Pine'"));
	if (FindWhiteMaterial.Object != NULL)
	{
		MaterialWhite = (UMaterial*)FindWhiteMaterial.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FindBlackMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Walnut.M_Wood_Walnut'"));
	if (FindBlackMaterial.Object != NULL)
	{
		MaterialBlack = (UMaterial*)FindBlackMaterial.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FindGlowingMaterial(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Glowing.M_CobbleStone_Glowing'"));
	if (FindGlowingMaterial.Object != NULL)
	{
		MaterialGlowing = (UMaterial*)FindGlowingMaterial.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FindSelectableMaterial(TEXT("Material'/Game/Puzzle/Materials/SelectableMaterial.SelectableMaterial'"));
	if (FindSelectableMaterial.Object != NULL)
	{
		MaterialSelectable = (UMaterial*)FindSelectableMaterial.Object;
	}

	
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindPawnMesh(TEXT("StaticMesh'/Game/Puzzle/Meshes/pawn.pawn'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindKnightMesh(TEXT("StaticMesh'/Game/Puzzle/Meshes/knight.knight'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindTowerMesh(TEXT("StaticMesh'/Game/Puzzle/Meshes/tower.tower'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindBishopMesh(TEXT("StaticMesh'/Game/Puzzle/Meshes/bishop.bishop'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindQueenMesh(TEXT("StaticMesh'/Game/Puzzle/Meshes/queen.queen'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FindKingMesh(TEXT("StaticMesh'/Game/Puzzle/Meshes/king.king'"));
		
	PieceMeshes[PAWN]   = FindPawnMesh.Object;
	PieceMeshes[KNIGHT] = FindKnightMesh.Object;
	PieceMeshes[TOWER]  = FindTowerMesh.Object;
	PieceMeshes[BISHOP] = FindBishopMesh.Object;
	PieceMeshes[KING]   = FindKingMesh.Object;
	PieceMeshes[QUEEN]  = FindQueenMesh.Object;

}

void AChessPiece::setColor( bool white )
{
	isWhite = white;
	DefaultMaterial = isWhite ? MaterialWhite : MaterialBlack;
	PieceMesh->SetMaterial(0, DefaultMaterial );
}

void AChessPiece::setSelected(bool selected)
{
	PieceMesh->SetMaterial(0, selected ? MaterialGlowing : DefaultMaterial);
}

void AChessPiece::setSelectable(bool selectable)
{
	isSelectable = selectable;
	PieceMesh->SetMaterial(0, isSelectable ? MaterialSelectable : DefaultMaterial);
}

void AChessPiece::setPieceType(PieceType type)
{
	PieceMesh->SetStaticMesh(PieceMeshes[type]);
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChessPiece::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AChessPiece::PieceClicked(UPrimitiveComponent* ClickedComp)
{
	if( isSelectable )
	{
		BlockGrid->makeMove(this);
	}
	else if (BlockGrid->IsReady())
	{
		setSelected(true);
		BlockGrid->onPieceSelected(this);
	}
}


void AChessPiece::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	PieceClicked(TouchedComponent);
}
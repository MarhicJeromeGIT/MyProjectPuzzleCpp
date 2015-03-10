// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPuzzleCpp.h"
#include "MyProjectPuzzleCppBlockGrid.h"
#include "MyProjectPuzzleCppBlock.h"
#include "Components/TextRenderComponent.h"
#include "ChessPiece.h"

#include "../../ThirdParty/Pulse/Includes/PulseLib.h"


AMyProjectPuzzleCppBlockGrid::AMyProjectPuzzleCppBlockGrid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(-200, 0.f, 0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ScoreText->SetText(TEXT("Score: 0"));
	ScoreText->AttachTo(DummyRoot);
	ScoreText->SetTextRenderColor(FColor::Black);

	// Set defaults
	Size = 3;
	BlockSpacing = 46.0f;

	lib = NULL;

}

void AMyProjectPuzzleCppBlockGrid::movePawn_Implementation(AChessPiece* piece, FVector destination)
{
	// Do nothing.
}

void AMyProjectPuzzleCppBlockGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AMyProjectPuzzleCppBlockGrid::InitChessGrid()
{
	targettedPiece = NULL;
	selectedPiece = NULL;
	turnFinished = true;
	AIisWhite = false;
	WhiteTurn = true;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Checkboard[i][j] = NULL;
		}
	}

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	//AMyProjectPuzzleCppBlock* dsada = GetWorld()->SpawnActor<AMyProjectPuzzleCppBlock>(GetActorLocation(), FRotator(0, 0, 0));

	// Place the pieces in the starting position :
	for( int i = 0; i < 8; i++ )
	{
		//const float XOffset = BlockSpacing; // Divide by dimension
		//const float YOffset = BlockSpacing; // Modulo gives remainder
		FVector BlockLocation[4];
		BlockLocation[0] = FVector(0.0, i * BlockSpacing, 0.f) + GetActorLocation();
		BlockLocation[1] = FVector(BlockSpacing, i * BlockSpacing, 0.f) + GetActorLocation();
		BlockLocation[2] = FVector(6 * BlockSpacing, i * BlockSpacing, 0.f) + GetActorLocation();
		BlockLocation[3] = FVector(7 * BlockSpacing, i * BlockSpacing, 0.f) + GetActorLocation();

		for (int p = 0; p < 4; p++)
		{
			int VertRot = (p < 2) ? 180 : 0;
			AChessPiece* newPiece = GetWorld()->SpawnActor<AChessPiece>(BlockLocation[p], FRotator(0, VertRot, 0));
			if (newPiece != NULL)
			{
				newPiece->BlockGrid = this;
				newPiece->file = i;
				int rank[] = { 0, 1, 6, 7 };
				newPiece->rank = rank[p];

				Checkboard[rank[p]][i] = newPiece;

				newPiece->setPieceType(AChessPiece::PAWN);
				newPiece->setColor( p < 2 ); // p<2 => WHITE
			}
		}
	}

	Checkboard[0][0]->setPieceType(AChessPiece::TOWER);
	Checkboard[0][1]->setPieceType(AChessPiece::KNIGHT);
	Checkboard[0][2]->setPieceType(AChessPiece::BISHOP);
	Checkboard[0][3]->setPieceType(AChessPiece::QUEEN);
	Checkboard[0][4]->setPieceType(AChessPiece::KING);
	Checkboard[0][5]->setPieceType(AChessPiece::BISHOP);
	Checkboard[0][6]->setPieceType(AChessPiece::KNIGHT);
	Checkboard[0][7]->setPieceType(AChessPiece::TOWER);

	Checkboard[7][0]->setPieceType(AChessPiece::TOWER);
	Checkboard[7][1]->setPieceType(AChessPiece::KNIGHT);
	Checkboard[7][2]->setPieceType(AChessPiece::BISHOP);
	Checkboard[7][3]->setPieceType(AChessPiece::QUEEN);
	Checkboard[7][4]->setPieceType(AChessPiece::KING);
	Checkboard[7][5]->setPieceType(AChessPiece::BISHOP);
	Checkboard[7][6]->setPieceType(AChessPiece::KNIGHT);
	Checkboard[7][7]->setPieceType(AChessPiece::TOWER);

	// Initialize the Chess engine :
	if (lib != NULL)
		delete lib;
	lib = new pulse::PulseLib();
	lib->startGame();

}

void AMyProjectPuzzleCppBlockGrid::BeginTurn()
{
	turnFinished = false;
	WhiteTurn = !WhiteTurn;
}

void AMyProjectPuzzleCppBlockGrid::EndTurn()
{
	turnFinished = true;
}

bool AMyProjectPuzzleCppBlockGrid::IsAITurn()
{
	return(AIisWhite == WhiteTurn);
}

void AMyProjectPuzzleCppBlockGrid::play()
{
	BeginTurn();

	static pulse::PulseLib::myMove move;
	lib->play(move);
	//cout << file[move.origFile] << move.origRank << " -> " << file[move.destFile] << move.destRank << endl;

	AChessPiece* piece = Checkboard[move.origRank][move.origFile];
	if (piece != NULL)
	{
		Checkboard[move.origRank][move.origFile] = NULL;
		if (Checkboard[move.destRank][move.destFile] != NULL)
		{
			targettedPiece = Checkboard[move.destRank][move.destFile];
			//Checkboard[move.destRank][move.destFile]->Destroy();
		}
		Checkboard[move.destRank][move.destFile] = piece;

		piece->file = move.destFile;
		piece->rank = move.destRank;

		FVector newLoc = FVector((move.destRank) * BlockSpacing, move.destFile * BlockSpacing, 0.f) + GetActorLocation();
		movePawn(piece, newLoc);

		char file[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
		FString ScoreString = FString::Printf(TEXT("AI MOVE : %c%d -> %c%d"),  file[move.origFile], move.origRank, file[move.destFile], move.destRank);
		ScoreText->SetText(ScoreString);
	}
	else
	{
		char file[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
		FString ScoreString = FString::Printf(TEXT("ERROR MOVE : %d : %c%d -> %c%d"), move.code, file[move.origFile], move.origRank, file[move.destFile], move.destRank);
		ScoreText->SetText(ScoreString);
	}

}

void AMyProjectPuzzleCppBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	FString ScoreString = FString::Printf(TEXT("Score: %d"), Score);
	ScoreText->SetText(ScoreString);
}

void AMyProjectPuzzleCppBlockGrid::onPieceSelected(AChessPiece* piece)
{
	for (int i = 0; i < SpawnedLegalMoveCubes.Num(); i++)
	{
		SpawnedLegalMoveCubes[i]->Destroy();
	}
	SpawnedLegalMoveCubes.Empty();


	if (selectedPiece != NULL && selectedPiece != piece )
	{
		selectedPiece->setSelected(false);
	}
	selectedPiece = piece;

	int file = piece->file;
	int rank = piece->rank;
	// get the list of legal moves for this piece :
	std::vector<pulse::PulseLib::myMove> moves;
	lib->getMoveList( file, rank, moves);

	for (int i = 0; i < moves.size(); i++)
	{
		int destFile = moves[i].destFile;
		int destRank = moves[i].destRank;
		if( Checkboard[destRank][destFile] != NULL ) // we are taking over a piece here
		{
			// we may now click on it
			Checkboard[destRank][destFile]->setSelectable(true);
		}
		else
		{
			FVector BlockLocation = FVector(moves[i].destRank * BlockSpacing, moves[i].destFile * BlockSpacing, 0.f) + GetActorLocation();
			AMyProjectPuzzleCppBlock* newPiece = GetWorld()->SpawnActor<AMyProjectPuzzleCppBlock>(BlockLocation, FRotator(0, 0, 0));
			SpawnedLegalMoveCubes.Push(newPiece);

			newPiece->OwningGrid = this;
			newPiece->file = moves[i].destFile;
			newPiece->rank = moves[i].destRank;
		}
	}	
}

AChessPiece* AMyProjectPuzzleCppBlockGrid::getTargettedPiece()
{
	return targettedPiece; 
}

void AMyProjectPuzzleCppBlockGrid::makeMove( int destFile, int destRank )
{
	BeginTurn();

	static int origFile = 0;
	static int origRank = 0;
	origFile = selectedPiece->file;
	origRank = selectedPiece->rank;

	Checkboard[origRank][origFile] = NULL;
	if (Checkboard[destRank][destFile] != NULL)
	{
		targettedPiece = Checkboard[destRank][destFile];
		//Checkboard[destRank][destFile]->Destroy();
	}
	Checkboard[destRank][destFile] = selectedPiece;

	selectedPiece->file = destFile;
	selectedPiece->rank = destRank;
	
	selectedPiece->setSelected(false);

	pulse::PulseLib::myMove move(origFile, origRank, destFile, destRank );
	lib->makeMove(move);

	FVector newLoc = FVector(destRank*BlockSpacing, (destFile)* BlockSpacing, 0.f) + GetActorLocation();
	movePawn(selectedPiece, newLoc);
	selectedPiece = NULL;

	for (int i = 0; i < SpawnedLegalMoveCubes.Num(); i++)
	{
		SpawnedLegalMoveCubes[i]->Destroy();
	}
	SpawnedLegalMoveCubes.Empty();
	for( int i=0; i< 8; i++ )
	{
		for( int j=0; j< 8; j++ )
		{
			if( Checkboard[i][j] != NULL )
			{
				Checkboard[i][j]->setSelectable(false);
			}
		}
	}
}

void AMyProjectPuzzleCppBlockGrid::makeMove(AChessPiece* destination)
{
	makeMove( destination->file, destination->rank );
}

void AMyProjectPuzzleCppBlockGrid::makeMove(AMyProjectPuzzleCppBlock* destination)
{
	makeMove( destination->file, destination->rank );
}
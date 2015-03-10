// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "../../ThirdParty/Pulse/Includes/PulseLib.h"
#include "MyProjectPuzzleCppBlockGrid.generated.h"


class AChessPiece;
class AMyProjectPuzzleCppBlock;

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class AMyProjectPuzzleCppBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:

	AChessPiece* Checkboard[8][8];

	UClass* MyPawnClass;

	AMyProjectPuzzleCppBlockGrid(const FObjectInitializer& ObjectInitializer);

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	bool turnFinished;

	virtual void BeginPlay() override;

	// Begin AActor interface
	UFUNCTION(BlueprintCallable, Category = Chess)
	virtual void InitChessGrid();
	

	bool AIisWhite;
	bool WhiteTurn; // White should play next
	UFUNCTION(BlueprintCallable, Category = Chess)
	virtual void EndTurn();

	UFUNCTION(BlueprintCallable, Category = Chess)
	virtual bool IsAITurn();

	virtual void BeginTurn();
	bool IsReady(){ return turnFinished; }

	// End AActor interface

	AChessPiece* targettedPiece;
	UFUNCTION(BlueprintCallable, Category = Chess)
	AChessPiece* getTargettedPiece();

	UFUNCTION(BlueprintNativeEvent, Category = Chess)
	void movePawn(AChessPiece* piece, FVector destination);

	/** Handle the block being clicked */
	void AddScore();

	TArray<AActor*> SpawnedLegalMoveCubes;


	AChessPiece* selectedPiece;
	void onPieceSelected(AChessPiece* piece);
	void makeMove(AMyProjectPuzzleCppBlock* destination);

	UFUNCTION(BlueprintCallable, Category = Chess)
	void play();

	pulse::PulseLib* lib;
public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

class AMyProjectPuzzleCppBlockGrid;


UCLASS(minimalapi)
class AChessPiece : public AActor
{
	GENERATED_BODY()
	
	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PieceMesh;  


public:	
	AMyProjectPuzzleCppBlockGrid* BlockGrid;

	int file;
	int rank;

	// Sets default values for this actor's properties
	AChessPiece(const FObjectInitializer& ObjectInitializer);

	UMaterial* MaterialWhite;
	UMaterial* MaterialBlack;
	UMaterial* MaterialGlowing;
	UMaterial* DefaultMaterial;
	UMaterial* MaterialSelectable;

	bool isWhite;
	bool isSelectable;
	void setColor( bool isWhite );
	void setSelected(bool selected);
	void setSelectable(bool selectable);

	enum PieceType
	{
		PAWN,
		KNIGHT,
		TOWER,
		BISHOP,
		QUEEN,
		KING
	};
	UStaticMesh* PieceMeshes[2];
	void setPieceType(PieceType type);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Handle the piece being clicked */
	UFUNCTION(BlueprintCallable, Category = Chess)
	void PieceClicked(UPrimitiveComponent* ClickedComp);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

};


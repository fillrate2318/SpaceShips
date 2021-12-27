// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TileToSpawn.generated.h"

class ACPP_Board;		// forward-declaration
class ACPP_PlayerShip;
class ACPP_OpponentShip;

UCLASS()
class BOARDGAME_API ACPP_TileToSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TileToSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Visualisation")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visualisation")
	UMaterialInterface* HighlightMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visualisation")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TileProperties")
	int32 Index;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TileProperties")
	TArray<int32> ClosestNeighbors;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TileProperties")
	TArray<int32> ReachableTiles;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TileProperties")
	bool IsEmpty;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TileProperties")
	ACPP_PlayerShip* PlayerShip;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TileProperties")
	ACPP_OpponentShip* OpponentShip;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "TileProperties")
	ACPP_Board* Board;

	UFUNCTION(BlueprintCallable, Category = "Visualisation")
	void HighlightNeighbors();

	UFUNCTION(BlueprintCallable, Category = "Board Logic")
	void UpdateReachableTiles();

	UFUNCTION(BlueprintCallable, Category = "Visualisation")
	void RemoveHighlight();

	UFUNCTION(BlueprintCallable, Category = "Player Action")
	void MoveShip();
};

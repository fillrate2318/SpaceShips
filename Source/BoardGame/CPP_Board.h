// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TileToSpawn.h"
#include "CPP_BorderToSpawn.h"
#include "CPP_PlayerShip.h"
#include "CPP_OpponentShip.h"
#include "CPP_Board.generated.h"

UCLASS()
class BOARDGAME_API ACPP_Board : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Board();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Initialization")
	FString FileName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Initialization")
	TArray<uint8> Board;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Initialization")
	TArray<ACPP_TileToSpawn*> TilesArray;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "MapSettings")
	int32 BoardSize;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "MapSettings")
	int32 TileSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapSettings")
	TArray<int32> PlayerShipLocations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapSettings")
	TArray<int32> OpponentShipLocations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapSettings")
	TMap<int32, int32> TeleportLocations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MapSettings")
	int32 PointsPerMove;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "State")
	ACPP_PlayerShip* SelectedShip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	FString SelectedMode;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SpawnLocation")
	FVector SpawnLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SpawnLocation")
	float StartLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnedActors")
	TArray<ACPP_PlayerShip*> SpawnedPlayerShips;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnedActors")
	TArray<ACPP_OpponentShip*> SpawnedOpponentShips;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActorsToSpawn")
	TSubclassOf<ACPP_TileToSpawn> TileToSpawnClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActorsToSpawn")
	TSubclassOf<ACPP_BorderToSpawn> BorderToSpawnClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActorsToSpawn")
	TSubclassOf<ACPP_PlayerShip> PlayerShipClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ActorsToSpawn")
	TSubclassOf<ACPP_OpponentShip> OpponentShipClass;



	UFUNCTION(BlueprintCallable, Category = "Initialization")
	FString ReadMapConfiguration();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void FileStringToIntArray(FString FileString);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnBoard();

	UFUNCTION(BlueprintCallable, Category = "SpawnLocation")
	void ChangeSpawnLocationX();

	UFUNCTION(BlueprintCallable, Category = "SpawnLocation")
	void ChangeSpawnLocationY();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	ACPP_TileToSpawn* SpawnTileActor(int TileIndex);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnBorderActor();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	ACPP_PlayerShip* SpawnPlayerShipActor();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	ACPP_OpponentShip* SpawnOpponentShipActor();

	UFUNCTION(BlueprintCallable, Category = "TileInitialization")
	void SetNeighbors(ACPP_TileToSpawn* Tile);

	UFUNCTION(BlueprintCallable, Category = "Update")
	void UpdateShipStats();

	UFUNCTION(BlueprintCallable, Category = "Update")
	void PerformOpponentAction(FString Action, int StartField, int TargetField);
};

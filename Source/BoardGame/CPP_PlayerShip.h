// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TileToSpawn.h"
#include "CPP_PlayerShip.generated.h"

UCLASS()
class BOARDGAME_API ACPP_PlayerShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_PlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Current tile reference of player ship */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	ACPP_TileToSpawn* Tile;

	/** Reference to the board */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State")
	ACPP_Board* Board;

	/** List of opponent ships that can be attacked */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State")
	TArray<ACPP_OpponentShip*> ReachableEnemies;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ship Stats")
	int32 HealthPoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
	int32 ActionPoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
	int32 Bullets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
	int32 Transfers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
	int32 Moves;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ship Stats")
	int32 Damage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ship Stats")
	int32 AttackRadius;

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitShipStats();

	UFUNCTION(BlueprintCallable, Category = "Player Action")
	void SelectShip();

	UFUNCTION(BlueprintCallable, Category = "Player Action")
	bool PassPoints();

	UFUNCTION(BlueprintCallable, Category = "Player Action")
	void ReceiveDamage(ACPP_OpponentShip* OpponentShip);

	UFUNCTION(BlueprintCallable, Category = "Visualisation")
	void HighlightEnemies();

	UFUNCTION(BlueprintCallable, Category = "Visualisation")
	void RemoveHighlight();

	UFUNCTION(BlueprintCallable, Category = "JsonCommunication")
	TMap<FString, int32> CreateJsonData();
};

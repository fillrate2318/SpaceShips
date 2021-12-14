// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_OpponentShip.generated.h"

class ACPP_Board;
class ACPP_PlayerShip;
class ACPP_TileToSpawn;

UCLASS()
class BOARDGAME_API ACPP_OpponentShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_OpponentShip();

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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
		ACPP_TileToSpawn* Tile;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State")
		ACPP_Board* Board;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ship Stats")
		int32 HealthPoints;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ship Stats")
		int32 ActionPoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
		int32 Bullets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
		int32 Transfers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ship Stats")
		int32 Moves;

	UFUNCTION(BlueprintCallable, Category = "Visualisation")
		void HighlightEnemy();

	UFUNCTION(BlueprintCallable, Category = "Visualisation")
		void RemoveHighlight();

	UFUNCTION(BlueprintCallable, Category = "Player Action")
		void ReceiveDamage();

	UFUNCTION(BlueprintCallable, Category = "JsonCommunication")
		TMap<FString, int32> CreateJsonData();
};

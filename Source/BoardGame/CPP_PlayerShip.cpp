// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerShip.h"

#include "CPP_Board.h"

// Sets default values
ACPP_PlayerShip::ACPP_PlayerShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitShipStats();

	Damage = 1;
	AttackRadius = 3;
}

// Called when the game starts or when spawned
void ACPP_PlayerShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_PlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_PlayerShip::InitShipStats()
{
	ActionPoints = 3;
	HealthPoints = 3;
	Bullets = 1;
	Transfers = 1;
	Moves = 3;
}


void ACPP_PlayerShip::SelectShip()
{
	if (Board->SelectedShip != nullptr)
	{
		Board->SelectedShip->Tile->RemoveHighlight();
		Board->SelectedShip->RemoveHighlight();
	}
	Board->SelectedShip = this;
	if (ActionPoints != 0)
	{
		Tile->UpdateReachableTiles();
		Tile->HighlightNeighbors();
		HighlightEnemies();
	}
}

bool ACPP_PlayerShip::PassPoints()
{
	if (Board->SelectedMode == "PassPoints" && Transfers != 0)
	{
		Board->SelectedShip->ActionPoints--;
		ActionPoints++;
		Transfers--;
		return true;
	}
	return false;
}


void ACPP_PlayerShip::HighlightEnemies()
{
	RemoveHighlight();
	ReachableEnemies.Empty();
	const int32 TileIndex = Tile->Index;
	const uint16 BoardSize = Board->BoardSize;
	for (int j = -1; j <= 1; j++)
	{
		for (int i = -1; i <= 1; i++)
		{
			for (int k = 1; k <= AttackRadius + 1; k++)
			{
				const int TargetTileIndex = TileIndex + (BoardSize * j * k) + (i * k);
				if (TargetTileIndex < 0 || TargetTileIndex > pow(BoardSize, 2))
				{
					break;
				}
				ACPP_TileToSpawn* TargetTile = Board->TilesArray[TargetTileIndex];
				if (TargetTile == nullptr) {
					break;
				} 
				if (TargetTile->OpponentShip != nullptr)
				{
					ReachableEnemies.Add(TargetTile->OpponentShip);
				}
			}
		}
	}
	for (ACPP_OpponentShip* OpponentShip : ReachableEnemies)
	{
		OpponentShip->HighlightEnemy();
	}
}

void ACPP_PlayerShip::RemoveHighlight()
{
	for (ACPP_OpponentShip* OpponentShip : ReachableEnemies)
	{
		OpponentShip->RemoveHighlight();
	}
}

void ACPP_PlayerShip::ReceiveDamage(ACPP_OpponentShip* OpponentShip)
{
	HealthPoints -= OpponentShip->Damage;
	if (HealthPoints == 0)
	{
		Destroy();
	}
	OpponentShip->ActionPoints--;
	OpponentShip->Bullets--;
}

TMap<FString, int32> ACPP_PlayerShip::CreateJsonData()
{
	TMap<FString, int32> JsonData;
	JsonData.Add(TEXT("coords"), Tile->Index);
	JsonData.Add(TEXT("hp"), HealthPoints);
	JsonData.Add(TEXT("mp"), ActionPoints);
	JsonData.Add(TEXT("bullets"), Bullets);
	JsonData.Add(TEXT("transfers"), Transfers);
	JsonData.Add(TEXT("moves"), Moves);
	return JsonData;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TileToSpawn.h"

#include "CPP_Board.h"

// Sets default values
ACPP_TileToSpawn::ACPP_TileToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
	IsEmpty = true;
}

// Called when the game starts or when spawned
void ACPP_TileToSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_TileToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_TileToSpawn::HighlightNeighbors()
{
	for (const int32 Tile : ReachableTiles)
	{
		if (Board->TilesArray[Tile]->IsEmpty)
		{
			Board->TilesArray[Tile]->MeshComponent->SetMaterial(0, HighlightMaterial);
		}
	}
}

void ACPP_TileToSpawn::UpdateReachableTiles()
{
	int Depth = 1;
	ReachableTiles.Empty();
	if (Board->SelectedShip != nullptr)
	{
		ReachableTiles.Append(Board->SelectedShip->Tile->ClosestNeighbors);
		while (Depth != PlayerShip->ActionPoints)
		{
			const int Length = ReachableTiles.Num();
			for (int i = 0; i < Length; i++)
			{
				for (int32 Move : Board->TilesArray[ReachableTiles[i]]->ClosestNeighbors)
				{
					if (!ReachableTiles.Contains(Move))
					{
						ReachableTiles.Add(Move);
					}
				}
			}
			Depth++;
		}

		ReachableTiles.Remove(Index);

		for (const int32 TileIndex : ReachableTiles)
		{
			ReachableTiles.Add(TileIndex);
		}
	}
}


void ACPP_TileToSpawn::RemoveHighlight()
{
	for (int32 Move : ReachableTiles)
	{
		Board->TilesArray[Move]->MeshComponent->SetMaterial(0, DefaultMaterial);
	}
}


void ACPP_TileToSpawn::MoveShip()
{
	if (Board->SelectedShip)
	{
		Board->SelectedShip->Tile->UpdateReachableTiles();
		if (Board->SelectedShip->Tile->ReachableTiles.Contains(Index))
		{
			if (Board->SelectedShip->ActionPoints != 0 && Board->SelectedShip->Moves != 0)
			{
				Board->SelectedShip->Tile->RemoveHighlight();
				Board->SelectedShip->Tile->IsEmpty = true;

				Board->SelectedShip->Tile = this;
				Board->SelectedShip->Tile->IsEmpty = false;

				Board->SelectedShip->SetActorLocation(GetActorLocation());
				Board->SelectedShip->HighlightEnemies();

				Board->SelectedShip->ActionPoints--;
				Board->SelectedShip->Moves--;

				if (Board->SelectedShip->ActionPoints == 0 || Board->SelectedShip->Moves == 0)
				{
					Board->SelectedShip->Tile->RemoveHighlight();
				}
				else
				{
					HighlightNeighbors();
				}


			}
			else
			{
				Board->SelectedShip->Tile->RemoveHighlight();
			}
		}
		else
		{
			Board->SelectedShip->Tile->RemoveHighlight();
			Board->SelectedShip = nullptr;
		}
		
		/*
		if (Board->SelectedShip->Tile->ValidMoves.Contains(Index))
		{
			if (Board->SelectedShip->ActionPoints != 0 && Board->SelectedShip->Moves != 0)
			{
				Board->SelectedShip->Tile->RemoveHighlight();
				Board->SelectedShip->Tile->IsEmpty = true;

				Board->SelectedShip->Tile = this;
				Board->SelectedShip->Tile->IsEmpty = false;

				Board->SelectedShip->SetActorLocation(GetActorLocation());
				Board->SelectedShip->HighlightEnemies();

				Board->SelectedShip->ActionPoints--;
				Board->SelectedShip->Moves--;

				if (Board->SelectedShip->ActionPoints == 0 || Board->SelectedShip->Moves == 0)
				{
					Board->SelectedShip->Tile->RemoveHighlight();
				}
				else
				{
					HighlightNeighbors();
				}

				
			}
			else
			{
				Board->SelectedShip->Tile->RemoveHighlight();
			}
		}
		else
		{
			Board->SelectedShip->Tile->RemoveHighlight();
			Board->SelectedShip = nullptr;
		}
		*/
	}
}

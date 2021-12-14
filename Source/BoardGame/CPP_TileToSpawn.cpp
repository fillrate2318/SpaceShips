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
	for (int32 Move : ValidMoves)
	{
		ACPP_TileToSpawn* Tile = Board->TilesArray[Move];
		if (Tile->IsEmpty)
		{
			Board->TilesArray[Move]->MeshComponent->SetMaterial(0, HighlightMaterial);
		}
	}
}

void ACPP_TileToSpawn::RemoveHighlight()
{
	for (int32 Move : ValidMoves)
	{
		Board->TilesArray[Move]->MeshComponent->SetMaterial(0, DefaultMaterial);
	}
}


void ACPP_TileToSpawn::MoveShip()
{
	if (Board->SelectedShip != nullptr)
	{
		if (!this->IsEmpty)
		{
			return;
		}
		/*
		if (Board->SelectedShip->ActionPoints != 0 && Board->SelectedMode == "Move")
		{
			if (Board->SelectedShip->Tile->ValidMoves.Contains(Index))
			{
				Board->SelectedShip->Tile->RemoveHighlight();
				Board->SelectedShip->Tile->IsEmpty = true;

				Board->SelectedShip->Tile = this;
				Board->SelectedShip->Tile->IsEmpty = false;

				Board->SelectedShip->SetActorLocation(GetActorLocation());
				Board->SelectedShip->HighlightEnemies();
				
				if (--Board->SelectedShip->ActionPoints != 0)
				{
					HighlightNeighbors();
				}
				
				//HighlightNeighbors();
			}
			else
			{
				Board->SelectedShip->Tile->RemoveHighlight();
				Board->SelectedShip = nullptr;
			}
		}
		else
		{
			Board->SelectedShip->Tile->RemoveHighlight();
		}
		*/
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
	}
}

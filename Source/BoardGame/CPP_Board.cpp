// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Board.h"
#include "Algo/Transform.h"

// Sets default values
ACPP_Board::ACPP_Board()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	FileName = "test_map_cpp.bin";
	FileStringToIntArray(ReadMapConfiguration());

	BoardSize = 13;
	TileSize = 110;
	PointsPerMove = 3;

	/*
	static ConstructorHelpers::FObjectFinder<TSubclassOf<ACPP_TileToSpawn>> TileActorReference(TEXT("Blueprint'/Game/Blueprints/World/BP_TileToSpawn.BP_TileToSpawn'"));
	TileToSpawn = *TileActorReference.Object;
	static ConstructorHelpers::FObjectFinder<TSubclassOf<ACPP_BorderToSpawn>> BorderActorReference(TEXT("Blueprint'/Game/Blueprints/World/BP_BorderToSpawn.BP_BorderToSpawn'"));
	BorderToSpawn = *BorderActorReference.Object;
	*/
}

// Called when the game starts or when spawned
void ACPP_Board::BeginPlay()
{
	Super::BeginPlay();
	SpawnBoard();
}

// Called every frame
void ACPP_Board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ACPP_Board::ReadMapConfiguration()
{
	FString FileString;
	const FString FileDestination = FPaths::ProjectContentDir() + TEXT("\\MapConfiguration\\") + FileName;
	FFileHelper::LoadFileToString(FileString, *FileDestination);
	return FileString;
}

void ACPP_Board::FileStringToIntArray(FString FileString)
{
	const int Length = FileString.Len();
	//UE_LOG(LogTemp, Warning, TEXT("%d\n"), Length);
	for(const TCHAR Char : FileString)
	{
		if(Char != ' ' && Char != '\n' && Char != '\r')
		{
			Board.Add(Char - 48);
		}
	}
}

void ACPP_Board::SpawnBoard()
{
	ACPP_TileToSpawn* SpawnedTile;
	for(int i = 0; i < pow(BoardSize, 2); i++)
	{
		if(i % BoardSize == 0)
		{
			ChangeSpawnLocationX();
		}
		switch(Board[i])
		{
			/*
			case(0):
				ChangeSpawnLocationY();
				TilesArray.Add(nullptr);
				break;
			*/
			case(0):
				SpawnedTile = SpawnTileActor(i);
				TilesArray.Add(SpawnedTile);
				if (PlayerShipLocations.Contains(i))
				{
					ACPP_PlayerShip* PlayerShip = SpawnPlayerShipActor();
					PlayerShip->Tile = SpawnedTile;
					SpawnedTile->PlayerShip = PlayerShip;
					SpawnedTile->IsEmpty = false;
				}
				if (OpponentShipLocations.Contains(i))
				{
					ACPP_OpponentShip* OpponentShip = SpawnOpponentShipActor();
					OpponentShip->Tile = SpawnedTile;
					SpawnedTile->OpponentShip = OpponentShip;
				}
				SetNeighbors(SpawnedTile);
				ChangeSpawnLocationY();
				break;
			case(1):
				SpawnBorderActor();
				ChangeSpawnLocationY();
				TilesArray.Add(nullptr);
				break;
			default:
				break;
		}
	}
}

void ACPP_Board::ChangeSpawnLocationX()
{
	StartLocation -= TileSize;
	SpawnLocation = FVector(StartLocation, 0.0, SpawnLocation.Z);
}

void ACPP_Board::ChangeSpawnLocationY()
{
	SpawnLocation += FVector(0, TileSize, 0);
}


ACPP_TileToSpawn* ACPP_Board::SpawnTileActor(int TileIndex)
{
	const FRotator Rotation = FRotator::ZeroRotator;
	ACPP_TileToSpawn* SpawnedTile = GetWorld()->SpawnActor<ACPP_TileToSpawn>(TileToSpawnClass, SpawnLocation, Rotation);
	SpawnedTile->Index = TileIndex;
	SpawnedTile->Board = this;
	return SpawnedTile;
}

void ACPP_Board::SpawnBorderActor()
{
	const FRotator Rotation = FRotator::ZeroRotator;
	GetWorld()->SpawnActor<ACPP_BorderToSpawn>(BorderToSpawnClass, SpawnLocation, Rotation);
}

ACPP_PlayerShip* ACPP_Board::SpawnPlayerShipActor()
{
	const FRotator Rotation = FRotator::ZeroRotator;
	ACPP_PlayerShip* PlayerShip = GetWorld()->SpawnActor<ACPP_PlayerShip>(PlayerShipClass, SpawnLocation, Rotation);
	PlayerShip->Board = this;
	SpawnedPlayerShips.Add(PlayerShip);
	return PlayerShip;
}

ACPP_OpponentShip* ACPP_Board::SpawnOpponentShipActor()
{
	const FRotator Rotation = FRotator::ZeroRotator;
	ACPP_OpponentShip* OpponentShip = GetWorld()->SpawnActor<ACPP_OpponentShip>(OpponentShipClass, SpawnLocation, Rotation);
	OpponentShip->Board = this;
	SpawnedOpponentShips.Add(OpponentShip);
	return OpponentShip;
}

void ACPP_Board::SetNeighbors(ACPP_TileToSpawn* Tile)
{
	const int TileIndex = Tile->Index;
	TArray<int32> ValidMoves;
	const int* TeleportTile = TeleportLocations.FindKey(TileIndex);
	if (TeleportTile != nullptr)
	{
		ValidMoves.Add(*TeleportTile);
	}
	for (int j = -1; j <= 1; j++)
	{
		for (int i = -1; i <= 1; i++)
		{
			const int TargetTileIndex = TileIndex + BoardSize * j + i;
			if (TargetTileIndex > 0 && TargetTileIndex < pow(BoardSize, 2))
			{
				if (TargetTileIndex / BoardSize == (TileIndex / BoardSize) + j)
				{
					if (Board[TargetTileIndex] == 0)
					{
						ValidMoves.Add(TargetTileIndex);
					}
				}
			}
		}
	}
	ValidMoves.Remove(TileIndex);
	Tile->ClosestNeighbors = ValidMoves;
}

void ACPP_Board::UpdateShipStats()
{
	for (ACPP_PlayerShip* PlayerShip : SpawnedPlayerShips)
	{
		PlayerShip->ActionPoints += PointsPerMove;
		PlayerShip->Bullets = 1;
		PlayerShip->Transfers = 1;
		PlayerShip->Moves = 3;
	}
}

void ACPP_Board::PerformOpponentAction(FString Action, int StartField, int TargetField)
{
	FTimerHandle UnusedHandle;
	if (StartField == NULL || TargetField == NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Error"));
		return;
	}
	else
	{
		
	}
	ACPP_TileToSpawn* StartTile = TilesArray[StartField];
	ACPP_TileToSpawn* TargetTile = TilesArray[TargetField];
	ACPP_OpponentShip* OpponentShip = StartTile->OpponentShip;

	UE_LOG(LogTemp, Warning, TEXT("%s %d %d"), *Action, StartField, TargetField);

	if (Action == "move")
	{
		if (OpponentShip != nullptr)
		{
			OpponentShip->MoveShip(TargetTile);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
	}
	else if (Action == "transfer")
	{
		if (StartTile->OpponentShip != nullptr && TargetTile->OpponentShip != nullptr)
		{
			StartTile->OpponentShip->ActionPoints--;
			TargetTile->OpponentShip->ActionPoints++;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
	}
	else if (Action == "shoot")
	{
		
	}
	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACPP_Board::TimerElapsed, TimerDelay, false);
}

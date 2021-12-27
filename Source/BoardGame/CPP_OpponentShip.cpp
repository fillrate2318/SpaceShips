// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_OpponentShip.h"

#include "CPP_Board.h"

// Sets default values
ACPP_OpponentShip::ACPP_OpponentShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);

	ActionPoints = 3;
	HealthPoints = 3;
	Bullets = 1;
	Transfers = 1;
	Moves = 3;
}

// Called when the game starts or when spawned
void ACPP_OpponentShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_OpponentShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_OpponentShip::HighlightEnemy()
{
	MeshComponent->SetMaterial(0, HighlightMaterial);
}

void ACPP_OpponentShip::RemoveHighlight()
{
	MeshComponent->SetMaterial(0, DefaultMaterial);
}

void ACPP_OpponentShip::ReceiveDamage()
{
	const ACPP_PlayerShip* PlayerShip = Board->SelectedShip;
	if (PlayerShip != nullptr && PlayerShip->ActionPoints != 0 && PlayerShip->Bullets != 0)
	{
		if (PlayerShip->ReachableEnemies.Contains(this))
		{
			HealthPoints -= PlayerShip->Damage;
			if (HealthPoints == 0)
			{
				Destroy();
			}
			Board->SelectedShip->ActionPoints--;
			Board->SelectedShip->Bullets--;
		}
	}
}

void ACPP_OpponentShip::MoveShip(ACPP_TileToSpawn* TargetTile)
{
	SetActorLocation(TargetTile->GetActorLocation());
	this->Tile->IsEmpty = true;
	this->Tile->OpponentShip = nullptr;
	this->Tile = TargetTile;
	TargetTile->OpponentShip = this;
	TargetTile->IsEmpty = false;
}

TMap<FString, int32> ACPP_OpponentShip::CreateJsonData()
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "Breach/PlayerControllers/PlayersController.h"
#include "KillEmAllGameMode.h"


AKillEmAllGameMode::AKillEmAllGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();
    RequiredKills = 2;
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	PController = Cast<APlayersController>(PawnKilled->GetController());
	UE_LOG(LogTemp, Error, TEXT("Pawn Detected"));
}

void AKillEmAllGameMode::NoOfPawnKilled(int32 IncreasedNo)
{
	Super::NoOfPawnKilled(IncreasedNo);

	KillCount = KillCount + IncreasedNo;
	UE_LOG(LogTemp, Error, TEXT("Kill Increased"));
}

void AKillEmAllGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Error, TEXT("GameEnd is called"));

	if (KillCount == RequiredKills)
	{
		bPlayerWon = true;
		UE_LOG(LogTemp, Error, TEXT("You Won"));
	}

	if (PController->ReturnPlayerState())
	{
		bPlayerWon = false;
		UE_LOG(LogTemp, Error, TEXT("You Lost"));
	}
}
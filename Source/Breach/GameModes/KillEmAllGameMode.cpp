// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "Breach/AIControllers/BreachAIController.h"
#include "Breach/PlayerControllers/PlayersController.h"
#include "EngineUtils.h"

AKillEmAllGameMode::AKillEmAllGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();

	CurrentKills = 0;
}

void AKillEmAllGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	CurrentKills += 1;
	APlayersController* PController = Cast<APlayersController>(PawnKilled->GetController());
	if (PController != nullptr)
	{
		EndGame(false);
	}

	UE_LOG(LogTemp, Error, TEXT("Current Kills: %i"), CurrentKills);
	if (CurrentKills == RequiredKills)
	{
		EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "Breach/PlayerControllers/PlayersController.h"
#include "EngineUtils.h"


void AKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();
	CurrentKills = 0;
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	CurrentKills += 1;
	UE_LOG(LogTemp, Warning, TEXT("I have %i kills"), CurrentKills);
	if (CurrentKills == RequiredKills)
	{
		EndGame(true);
	}

	APlayersController* PController = Cast<APlayersController>(PawnKilled->GetController());
	if (PController != nullptr)
	{
		EndGame(false);
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
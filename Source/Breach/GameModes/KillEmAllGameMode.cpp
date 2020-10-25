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

	for (ABreachAIController* Enemy : TActorRange<ABreachAIController>(GetWorld()))
	{
		CurrentEnemies += 1;
	}
	UE_LOG(LogTemp, Warning, TEXT("Current Enemies: %i"), CurrentEnemies);
}

void AKillEmAllGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Error, TEXT("Current Enemies: %i"), CurrentEnemies);
	if (CurrentEnemies == RequiredEnemies)
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
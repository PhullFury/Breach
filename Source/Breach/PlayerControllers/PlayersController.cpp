// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "Breach/Characters/PlayerCharacter.h"
#include "PlayersController.h"
#include "TimerManager.h"


void APlayersController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void APlayersController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorld()->GetTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, 5);
}

bool APlayersController::ReturnPlayerState()
{
	APlayerCharacter* PShooter = Cast<APlayerCharacter>(GetPawn());
	
	return PShooter->IsDead();	
}
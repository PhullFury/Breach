// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayersController.h"
#include "Blueprint/UserWidget.h"
#include "Breach/Characters/PlayerCharacter.h"
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
	
	if (bIsWinner)
	{
		WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}	
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, 5);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Breach/GameModes/BreachGameMode.h"
#include "KillEmAllGameMode.generated.h"

class APlayersController;

UCLASS()
class BREACH_API AKillEmAllGameMode : public ABreachGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	bool bPlayerWon;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void EndGame(bool bIsPlayerWinner);


	UPROPERTY(EditAnywhere, Category = "Game")
		int32 RequiredKills = 2;
	int32 CurrentKills;
};
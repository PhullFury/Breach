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
	virtual void NoOfPawnKilled(int32 IncreasedNo) override;
	virtual void PawnKilled(APawn* PawnKilled) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AKillEmAllGameMode();

	bool bPlayerWon;


private:
	int32 KillCount = 0;
	APlayersController* PController;

	UPROPERTY(EditAnywhere, Category = "Kills")
		int32 RequiredKills = 1;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
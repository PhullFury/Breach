// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayersController.generated.h"

class UUSerWidget;
UCLASS()
class BREACH_API APlayersController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY()
		UUserWidget* HUD;
	UPROPERTY()
		UUserWidget* LoseScreen;
	UPROPERTY()
		UUserWidget* WinScreen;
	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> WinScreenClass;

	FTimerHandle RestartTimer;


public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
};

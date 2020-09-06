// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BreachAIController.generated.h"


UCLASS()
class BREACH_API ABreachAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = "AIBehavior")
		UBehaviorTree* AIBehavior;
	UPROPERTY(EditAnywhere, Category = "AIBehavior")
		float PatrolLenght = 2000;
};
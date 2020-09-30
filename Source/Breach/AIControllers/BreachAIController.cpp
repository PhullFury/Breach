// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BlackboardComponent.h"
#include "BreachAIController.h"
#include "Kismet/GameplayStatics.h"


void ABreachAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolStartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolEndLocation"), GetPawn()->GetActorLocation() + GetPawn()->GetActorRotation().Vector() * PatrolLenght);
	}
}

void ABreachAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABreachAIController::GetPlayerInSight()
{
	return bIsPlayerInSight;
}
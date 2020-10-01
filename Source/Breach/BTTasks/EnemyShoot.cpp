// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController.h"
#include "Breach/Characters/PlayerCharacter.h"
#include "EnemyShoot.h"
#include "Kismet/GameplayStatics.h"


UEnemyShoot::UEnemyShoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UEnemyShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	APlayerCharacter* Enemy = Cast<APlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	Enemy->EnemyShoot();
	return EBTNodeResult::Succeeded;
}
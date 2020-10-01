// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyShoot.generated.h"


UCLASS()
class BREACH_API UEnemyShoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEnemyShoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
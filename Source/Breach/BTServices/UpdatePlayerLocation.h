// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UpdatePlayerLocation.generated.h"



UCLASS()
class BREACH_API UUpdatePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UUpdatePlayerLocation();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
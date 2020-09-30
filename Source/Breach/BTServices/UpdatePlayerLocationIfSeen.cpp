// Fill out your copyright notice in the Description page of Project Settings.


#include "Breach/AIControllers/BreachAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UpdatePlayerLocationIfSeen.h"


UUpdatePlayerLocationIfSeen::UUpdatePlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UUpdatePlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;

	ABreachAIController* AIController = Cast<ABreachAIController>(OwnerComp.GetOwner());
	if (AIController == nullptr) return;

	bool bIsPlayerInSight = AIController->GetPlayerInSight();

	if (bIsPlayerInSight)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
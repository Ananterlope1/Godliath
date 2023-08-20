// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Roam.h"
#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_Roam::UBTService_Roam()
{
    NodeName="Roam";
}

void UBTService_Roam::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	AEnemyAIController* MyAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (NavSys && MyAI && MyAI->GetPawn())
	{
		const float SearchRadius = 1000.0f;
		FNavLocation RandomPt;
		
		const bool bFound = NavSys->GetRandomPointInNavigableRadius(MyAI->GetPawn()->GetActorLocation(), SearchRadius, RandomPt);
		if (bFound)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomPt.Location);
			
		}	
	}

}

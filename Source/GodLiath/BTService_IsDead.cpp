// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsDead.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_IsDead::UBTService_IsDead()
{
    NodeName = "Is Dead?";
}

void UBTService_IsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AEnemyAIController* CharacterAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (CharacterAI == nullptr)
    {
        return;    
    }

    bool IsCharacterDead = CharacterAI->IsDead();

    if (IsCharacterDead)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
    }else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
    }
}

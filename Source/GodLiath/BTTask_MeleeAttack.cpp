// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyCharacter.h"



UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    Character->SwingWeapon();

    return EBTNodeResult::Succeeded;
}

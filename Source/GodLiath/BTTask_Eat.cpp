// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Eat.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BerserkerCharacter.h"
#include "AIController.h"


UBTTask_Eat::UBTTask_Eat()
{
    NodeName = TEXT("Eat");
}

EBTNodeResult::Type UBTTask_Eat::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    ABerserkerCharacter* Character = Cast<ABerserkerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    Character->Eat();

    FName EatableName = TEXT("ClosestEatableActor");
    AEnemyCharacter* ClosestEatableActor = Cast<AEnemyCharacter>(BlackboardComp->GetValueAsObject(EatableName));  
    ClosestEatableActor->SetIsEatable(false);

    //Once eaten then set eatable to false

    return EBTNodeResult::Succeeded;
}

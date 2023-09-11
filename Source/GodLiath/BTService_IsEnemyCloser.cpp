// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsEnemyCloser.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BerserkerCharacter.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"


UBTService_IsEnemyCloser::UBTService_IsEnemyCloser()
{
    NodeName = "Is Enemy Closer Than Player?";
}


void UBTService_IsEnemyCloser::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }
    OwnerLocation = OwnerComp.GetOwner()->GetActorLocation();

    if (OwnerComp.GetBlackboardComponent())
    {
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        FName EnemyKeyID = FName(TEXT("ClosestEnemyLocation"));
        FVector ClosestEnemyLoc = BlackboardComp->GetValueAsVector(EnemyLocKey.SelectedKeyName); 
        // uint8* ClosestLocKey = BlackboardComp->GetK(KeyID);
        FName PlayerKeyID = FName(TEXT("LastKnownPlayerLocation"));
        FVector ClosestPlayerLoc = BlackboardComp->GetValueAsVector(PlayerLocKey.SelectedKeyName);  

        double DisToEnemy = FVector::Dist(OwnerLocation, ClosestEnemyLoc);
        double DisToPlayer = FVector::Dist(OwnerLocation, ClosestPlayerLoc);

        // UE_LOG(LogTemp, Error, TEXT("Enemy Distance:  %d"), DisToEnemy);
        // UE_LOG(LogTemp, Error, TEXT("Player Distance: %d"), DisToPlayer);

        if (DisToEnemy < DisToPlayer)
        {            
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        }else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
        }

    }   
}

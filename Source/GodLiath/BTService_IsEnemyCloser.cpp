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

    // OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValue(FName("LastKnownPlayerLocation"));
    if (OwnerComp.GetBlackboardComponent())
    {
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        FName EnemyKeyID = FName(TEXT("ClosestEnemyLocation"));
        FVector ClosestEnemyLoc = BlackboardComp->GetValueAsVector(EnemyLocKey.SelectedKeyName);  
        // uint8* ClosestLocKey = BlackboardComp->GetK(KeyID);
        FName PlayerKeyID = FName(TEXT("LastKnownPlayerLocation"));
        FVector ClosestPlayerLoc = BlackboardComp->GetValueAsVector(PlayerLocKey.SelectedKeyName);  
        
        
        UE_LOG(LogTemp, Display, TEXT("ClosestEnemyLocKey: %s"), *ClosestEnemyLoc.ToString());
        UE_LOG(LogTemp, Display, TEXT("ClosestPlayerLocKey: %s"), *ClosestPlayerLoc.ToString());

        if (FVector::Dist(OwnerLocation, ClosestEnemyLoc) < FVector::Dist(OwnerLocation, ClosestPlayerLoc))
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        }else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
        }

    }   
}

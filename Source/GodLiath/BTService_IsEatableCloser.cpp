// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsEatableCloser.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BerserkerCharacter.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"


UBTService_IsEatableCloser::UBTService_IsEatableCloser()
{
    NodeName = "Is Eatable Closer Than Player?";
}

void UBTService_IsEatableCloser::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
        FName EatableKeyID = FName(TEXT("ClosestEatableLocation"));
        FVector ClosestEatLoc = BlackboardComp->GetValueAsVector(EnemyLocKey.SelectedKeyName);  
        // uint8* ClosestLocKey = BlackboardComp->GetK(KeyID);
        FName PlayerKeyID = FName(TEXT("LastKnownPlayerLocation"));
        FVector ClosestPlayerLoc = BlackboardComp->GetValueAsVector(PlayerLocKey.SelectedKeyName);  
        
        
        // UE_LOG(LogTemp, Display, TEXT("ClosestEatLocKey: %s"), *ClosestEatLoc.ToString());
        // UE_LOG(LogTemp, Display, TEXT("ClosestPlayerLocKey: %s"), *ClosestPlayerLoc.ToString());
        // UE_LOG(LogTemp, Display, TEXT("ClosestEatLocKey: %d"), FVector::Dist(OwnerLocation, ClosestEatLoc));
        // UE_LOG(LogTemp, Display, TEXT("ClosestPlayerLocKey: %d"), FVector::Dist(OwnerLocation, ClosestPlayerLoc));


        if (FVector::Dist(OwnerLocation, ClosestEatLoc) < FVector::Dist(OwnerLocation, ClosestPlayerLoc))
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        }else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
        }

    }   

    
}

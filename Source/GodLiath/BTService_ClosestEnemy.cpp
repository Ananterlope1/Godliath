// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ClosestEnemy.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "Math/Vector.h"


UBTService_ClosestEnemy::UBTService_ClosestEnemy()
{
    NodeName = "Closest Enemy";
}

void UBTService_ClosestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    OwnerLocation = OwnerComp.GetOwner()->GetActorLocation();
    AEnemyAIController* SelfAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    // FString OwnerLoc = OwnerLocation.ToCompactString();
    // UE_LOG(LogTemp, Display, TEXT("Owner Location: %s"), *OwnerLoc);

    FVector ChosenClosestEnemyLocation;
    // Bool to say whether enemy location has been changed
    bool CheckForVectorChange = false;
    bool EnemyDetected = false;
    FVector PreviousClosestEnemyLocation;

    // UE_LOG(LogTemp, Warning, TEXT("Chosen Enemy location changed?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));

     // Check over all the Enemy actors and find the closest one.
    for (AEnemyAIController* EnemyAI : TActorRange<AEnemyAIController>(GetWorld()))
    {
        // UE_LOG(LogTemp, Display, TEXT("Check EnemyAI loop"));
        //Check that enemy isn't dead/ eatable and not the current AI
        if (EnemyAI->IsDead() == false && EnemyAI != SelfAI)
        {
            // UE_LOG(LogTemp, Display, TEXT("Check EnemyAliveAI loop"));

            ThisEnemyLocation = EnemyAI->GetPawn()->GetActorLocation();
            EnemyDetected = true;

            if (FVector::Dist(OwnerLocation, ThisEnemyLocation) <= FVector::Dist(OwnerLocation, PreviousClosestEnemyLocation))
            {
                ChosenClosestEnemyLocation = ThisEnemyLocation;
                CheckForVectorChange = true;
                EnemyPawn = Cast<AEnemyCharacter>(EnemyAI->GetPawn());
                FString EnemyName = EnemyPawn->GetName();
                // UE_LOG(LogTemp, Error, TEXT("Line Of Sight to Enemy: %s"), *EnemyName);
                // FString EnemyLoc = ChosenClosestEnemyLocation.ToCompactString();
                // UE_LOG(LogTemp, Error, TEXT("Enemy Location: %s"), *EnemyLoc);
            }
            PreviousClosestEnemyLocation = ChosenClosestEnemyLocation;
            // UE_LOG(LogTemp, Warning, TEXT("Chosen Enemy location changed in loop?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));
        }      

    }

    // UE_LOG(LogTemp, Warning, TEXT("Exit EnemyAI loop"));
    
    // FString ChosenEatVec = ChosenClosestEnemyLocation.ToCompactString();
    // UE_LOG(LogTemp, Error, TEXT("The returned chosen location: %s"), *ChosenEatVec);

    // UE_LOG(LogTemp, Warning, TEXT("Chosen Enemy location changed?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));
            
    if (EnemyDetected && OwnerComp.GetAIOwner()->LineOfSightTo(EnemyPawn))
    {
        // UE_LOG(LogTemp, Display, TEXT("Setting Line of sight to Enemy"));
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ChosenClosestEnemyLocation);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(EnemyActorKey.SelectedKeyName, EnemyPawn);

    }
    else
    {
        // UE_LOG(LogTemp, Error, TEXT("Clearing values of Enemy"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        OwnerComp.GetBlackboardComponent()->ClearValue(EnemyActorKey.SelectedKeyName);

    }



}

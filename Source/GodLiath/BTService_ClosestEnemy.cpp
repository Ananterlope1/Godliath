// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ClosestEnemy.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"


UBTService_ClosestEnemy::UBTService_ClosestEnemy()
{
    NodeName = "Closest Enemy";
}

void UBTService_ClosestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    OwnerLocation = OwnerComp.GetOwner()->GetActorLocation();
    AEnemyAIController* SelfAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    FString OwnerLoc = OwnerLocation.ToCompactString();
    UE_LOG(LogTemp, Display, TEXT("Owner Location: %s"), *OwnerLoc);

    FVector ChosenClosestEnemyLocation;

     // Check over all the Enemy actors and find the closest one.
    for (AEnemyAIController* EnemyAI : TActorRange<AEnemyAIController>(GetWorld()))
    {
         
        if (EnemyAI->IsDead() == false && EnemyAI != SelfAI)
        {
            UE_LOG(LogTemp, Display, TEXT("Check EnemyAI loop"));

            ThisEnemyLocation = EnemyAI->GetPawn()->GetActorLocation();
            FString EnemyVec = ThisEnemyLocation.ToCompactString();
            UE_LOG(LogTemp, Warning, TEXT("This EnemyLocation: %s"), *EnemyVec);

            // Or have a previous closest which is overwritten when another closer Enemy is found?
            double OwnThisEnemy = FVector::Dist(OwnerLocation, ThisEnemyLocation);
            UE_LOG(LogTemp, Warning, TEXT("Distance between OwnerLocation and This Enemy Loc : %d"), OwnThisEnemy);

            double OwnOldEnemy = FVector::Dist(OwnerLocation, PreviousClosestEnemyLocation);
            UE_LOG(LogTemp, Display, TEXT("Distance between OwnerLocation and Old Enemy Loc : %d"), OwnOldEnemy);


            if (FVector::Dist(OwnerLocation, ThisEnemyLocation) < FVector::Dist(OwnerLocation, PreviousClosestEnemyLocation))
            {
                ChosenClosestEnemyLocation = ThisEnemyLocation;
                EnemyPawn = Cast<AEnemyCharacter>(EnemyAI->GetPawn());
                FString EnemyName = EnemyPawn->GetName();
                UE_LOG(LogTemp, Error, TEXT("Line Of Sight to Enemy: %s"), *EnemyName);
            }
            PreviousClosestEnemyLocation = ChosenClosestEnemyLocation;
        }      

    }

    UE_LOG(LogTemp, Warning, TEXT("Exit EnemyAI loop"));
    
    FString ChosenEatVec = ChosenClosestEnemyLocation.ToCompactString();
    UE_LOG(LogTemp, Error, TEXT("The returned chosen location: %s"), *ChosenEatVec);

            
    if (ChosenClosestEnemyLocation.IsZero() == false && OwnerComp.GetAIOwner()->LineOfSightTo(EnemyPawn))
    {
        UE_LOG(LogTemp, Display, TEXT("Setting Line of sight to Enemy"));
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ChosenClosestEnemyLocation);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(EnemyActorKey.SelectedKeyName, EnemyPawn);

    }else
    {
        UE_LOG(LogTemp, Error, TEXT("Clearing values of Enemy"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        OwnerComp.GetBlackboardComponent()->ClearValue(EnemyActorKey.SelectedKeyName);

    }



}

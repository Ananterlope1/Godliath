// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ClosestEnemy.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "Math/Vector.h"
#include "MinionCharacter.h"


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
    // bool CheckForVectorChange = false;
    // bool EnemyDetected = false;
    // FVector PreviousClosestEnemyLocation;
    TArray<AActor*> ActorArrayToSort;
    // if(UWorld* World = GetWorld())
    // {
    //     UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), ActorArrayToSort);
    // }
    for (AEnemyAIController* EnemyAI : TActorRange<AEnemyAIController>(GetWorld()))
    {
        if (EnemyAI->IsDead() == false && EnemyAI != SelfAI && OwnerComp.GetAIOwner()->LineOfSightTo(EnemyAI->GetPawn()))
        {
            FString EnemyName = EnemyAI->GetPawn()->GetActorNameOrLabel();
            UE_LOG(LogTemp, Display, TEXT("Adding Close Enemy: %s"), *EnemyName);
            ActorArrayToSort.Emplace(EnemyAI->GetPawn());
        }
    }
    TArray<FActor_Dist> Sorted_Array;
    Distance_Sort(ActorArrayToSort, OwnerComp.GetOwner(), false, Sorted_Array);
    
    if (Sorted_Array.Num() > 0)
    {
        AActor* ClosestActor = Sorted_Array[0].actor;
        FString ClosestActorName = ClosestActor->GetActorNameOrLabel();
        UE_LOG(LogTemp, Warning, TEXT("ClosestActor IS : %s"), *ClosestActorName);
        FVector ClosestActorLocation = ClosestActor->GetActorLocation();
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ClosestActorLocation);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(EnemyActorKey.SelectedKeyName, ClosestActor);

    }
    else
    {
        // UE_LOG(LogTemp, Error, TEXT("Clearing values of Enemy"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        OwnerComp.GetBlackboardComponent()->ClearValue(EnemyActorKey.SelectedKeyName);

    }
    // AActor* ClosestActor = Sorted_Array[0].actor;
    // Sorted_Array[0].distance;


    // UE_LOG(LogTemp, Warning, TEXT("Chosen Enemy location changed?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));

     // Check over all the Enemy actors and find the closest one.
    // for (AEnemyAIController* EnemyAI : TActorRange<AEnemyAIController>(GetWorld()))
    // {
    //     // UE_LOG(LogTemp, Display, TEXT("Check EnemyAI loop"));
    //     //Check that enemy isn't dead/ eatable and not the current AI
    //     if (EnemyAI->IsDead() == false && EnemyAI != SelfAI)
    //     {
    //         // UE_LOG(LogTemp, Display, TEXT("Check EnemyAliveAI loop"));

    //         ThisEnemyLocation = EnemyAI->GetPawn()->GetActorLocation();
    //         EnemyDetected = true;
    //         // OwnerComp.GetAIOwner()->LineOfSightTo(EnemyAI->GetPawn()) ||

    //         if (FVector::Dist(OwnerLocation, ThisEnemyLocation) <= FVector::Dist(OwnerLocation, PreviousClosestEnemyLocation) || OwnerComp.GetAIOwner()->LineOfSightTo(EnemyAI->GetPawn()))
    //         {
    //             ChosenClosestEnemyLocation = ThisEnemyLocation;
    //             CheckForVectorChange = true;
    //             EnemyPawn = Cast<AEnemyCharacter>(EnemyAI->GetPawn());
    //             FString EnemyName = EnemyPawn->GetName();
    //             UE_LOG(LogTemp, Error, TEXT("Line Of Sight to Enemy: %s"), *EnemyName);
    //             FString EnemyLoc = ChosenClosestEnemyLocation.ToCompactString();
    //             // UE_LOG(LogTemp, Error, TEXT("Enemy Location: %s"), *EnemyLoc);
    //             PreviousClosestEnemyLocation = ChosenClosestEnemyLocation;
    //         }
    //         // PreviousClosestEnemyLocation = ChosenClosestEnemyLocation;
    //         // UE_LOG(LogTemp, Warning, TEXT("Chosen Enemy location changed in loop?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));
    //     }      

    // }

    // UE_LOG(LogTemp, Warning, TEXT("Exit EnemyAI loop"));
    
    // FString ChosenEatVec = ChosenClosestEnemyLocation.ToCompactString();
    // UE_LOG(LogTemp, Error, TEXT("The returned chosen location: %s"), *ChosenEatVec);

    // UE_LOG(LogTemp, Warning, TEXT("Chosen Enemy location changed?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));
//    && OwnerComp.GetAIOwner()->LineOfSightTo(EnemyPawn)
    // if (CheckForVectorChange && OwnerComp.GetAIOwner()->LineOfSightTo(EnemyPawn))
    // {
    //     FString EnemyName = EnemyPawn->GetName();
    //     // UE_LOG(LogTemp, Display, TEXT("Setting Line of sight to Enemy %s"), *EnemyName);
    //     OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ChosenClosestEnemyLocation);
    //     OwnerComp.GetBlackboardComponent()->SetValueAsObject(EnemyActorKey.SelectedKeyName, EnemyPawn);
    // }
    // else
    // {
    //     // UE_LOG(LogTemp, Error, TEXT("Clearing values of Enemy"));
    //     OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    //     OwnerComp.GetBlackboardComponent()->ClearValue(EnemyActorKey.SelectedKeyName);

    // }
    

}

void UBTService_ClosestEnemy::Distance_Sort(TArray <AActor*> Array_To_Sort, AActor* From_Actor, bool Descending, TArray <FActor_Dist> &Sorted_Array)
{
     if (Array_To_Sort.Num() > 0)            // check that input array is populated
    {
        TArray <FActor_Dist> Combined_Data; // define temporary array of custom struct variables
        FActor_Dist CurActor;
        FVector location1 = From_Actor->GetActorLocation(); // get the world location of the "central" actor distance will be measured from
        float length;
 
 
        for (int x = 0; x < Array_To_Sort.Num(); ++x)       // loop through all actors in array
        {
            FVector location2 = Array_To_Sort[x]->GetActorLocation();   // get world location of actor in array
            length = (location1 - location2).Size();                    // get distance between "central" actor and this actor from the array
            CurActor.distance = length;                                 // set the custom struct variable for distance
            CurActor.actor = Array_To_Sort[x];                          // set the custom struct actor 
 
            Combined_Data.Add(CurActor);                                // add the newly created struct to the temporary array
        }
 
        for (FActor_Dist x : Combined_Data)                             // using the distance value of each struct order the actors based on distance from "central" actor
        {
            int32 m = Combined_Data.Num();                              // run basic bubble sort algorithm
            int32 a, k;
            bool bDidSwap;
 
            for (a = 0; a < (m - 1); a++)
            {
                bDidSwap = false;
 
                if (Descending == true)                                 // sort high to low
                {
                    for (k = 0; k < m - a - 1; k++)
                    {
                        if (Combined_Data[k].distance < Combined_Data[k + 1].distance)
                        {
                            FActor_Dist z;
                            z = Combined_Data[k];
                            Combined_Data[k] = Combined_Data[k + 1];
                            Combined_Data[k + 1] = z;
                            bDidSwap = true;
                        }
                    }
 
                    if (bDidSwap == false)
                    {
                        break;
                    }
                }
                else                                                    // sort low to high
                {
                    for (k = 0; k < m - a - 1; k++)
                    {
                        if (Combined_Data[k].distance > Combined_Data[k + 1].distance)
                        {
                            FActor_Dist z;
                            z = Combined_Data[k];
                            Combined_Data[k] = Combined_Data[k + 1];
                            Combined_Data[k + 1] = z;
                            bDidSwap = true;
                        }
                    }
 
                    if (bDidSwap == false)
                    {
                        break;
                    }
                }
            }
 
            Sorted_Array = Combined_Data;                               // set output struct array to sorted temporary array
 
        }
    }
 
    else                                                                // if no elements in array exit function 
        ;
}


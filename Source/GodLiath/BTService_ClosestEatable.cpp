// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ClosestEatable.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MinionAIController.h"
#include "Kismet/GameplayStatics.h"
#include "MinionCharacter.h"


UBTService_ClosestEatable::UBTService_ClosestEatable()
{
    NodeName = TEXT("Closest Eatable Enemy");
}

void UBTService_ClosestEatable::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    OwnerLocation = OwnerComp.GetOwner()->GetActorLocation();
    FString OwnerLoc = OwnerLocation.ToCompactString();
    // UE_LOG(LogTemp, Display, TEXT("Owner Location: %s"), *OwnerLoc);

    FVector ChosenClosestEatableLocation;
    // Bool to say whether enemy location has been changed
    bool CheckForVectorChange = false;

    // UE_LOG(LogTemp, Warning, TEXT("Chosen Eatable location changed?: %s"), CheckForVectorChange? TEXT("true") : TEXT("false"));


    // Check over all the eatable actors and find the closest one.
    for (AMinionCharacter* MinionChar : TActorRange<AMinionCharacter>(GetWorld()))
    {
        // UE_LOG(LogTemp, Display, TEXT("Entering Eatable Minion Loop"));
                
        if (MinionChar->IsEatable() == true)
        {
            // UE_LOG(LogTemp, Display, TEXT("Check eatable loop"));

            ThisEatableLocation = MinionChar->GetTransform().GetLocation();
            // FString CheckEatVec = ThisEatableLocation.ToCompactString();
            // UE_LOG(LogTemp, Error, TEXT("The checked eatable location: %s"), *CheckEatVec);

            
            // ThisEatableLocation = MinionAI->GetPawn()->GetActorLocation();

            if (FVector::Dist(OwnerLocation, ThisEatableLocation) <= FVector::Dist(OwnerLocation, PreviousClosestEatableLocation))
            {
                ChosenClosestEatableLocation = ThisEatableLocation;
                CheckForVectorChange = true;
                EatablePawn = Cast<AMinionCharacter>(MinionChar);
                FString EatableName = EatablePawn->GetName();
                // UE_LOG(LogTemp, Error, TEXT("Line Of Sight to Eatable: %s"), *EatableName);
            }
            PreviousClosestEatableLocation = ChosenClosestEatableLocation;
        }      

    }

    

    // UE_LOG(LogTemp, Warning, TEXT("Exit eatable loop"));
    
    // FString ChosenEatVec = ChosenClosestEatableLocation.ToCompactString();
    // UE_LOG(LogTemp, Error, TEXT("The returned eatable location: %s"), *ChosenEatVec);

            
    if (CheckForVectorChange && OwnerComp.GetAIOwner()->LineOfSightTo(EatablePawn))
    {
        // UE_LOG(LogTemp, Display, TEXT("Setting Line of sight to eatable"));
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ChosenClosestEatableLocation);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(EatableActorKey.SelectedKeyName, EatablePawn);

    }else
    {
        // UE_LOG(LogTemp, Error, TEXT("Clearing values of eatable"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        OwnerComp.GetBlackboardComponent()->ClearValue(EatableActorKey.SelectedKeyName);

    }
    
}

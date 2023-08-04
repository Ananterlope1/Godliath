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
    UE_LOG(LogTemp, Display, TEXT("Owner Location: %s"), *OwnerLoc);

    FVector ChosenClosestEatableLocation;

    // Check over all the eatable actors and find the closest one.
    for (AMinionAIController* MinionAI : TActorRange<AMinionAIController>(GetWorld()))
    {
                
        if (MinionAI->IsEatable())
        {
            UE_LOG(LogTemp, Display, TEXT("Check MinionAI loop"));
            //Add location to TArray of FVectors? Loop over that and find closest?
            // MinionLocationArray.Emplace(MinionAI->GetFocusActor()->GetActorLocation());

            ThisEatableLocation = MinionAI->GetPawn()->GetActorLocation();
            FString EatableVec = ThisEatableLocation.ToCompactString();
            UE_LOG(LogTemp, Warning, TEXT("This EatableLocation: %s"), *EatableVec);

            // Or have a previous closest which is overwritten when another closer eatable is found?
            double OwnThisEatable = FVector::Dist(OwnerLocation, ThisEatableLocation);
            UE_LOG(LogTemp, Warning, TEXT("Distance between OwnerLocation and This eatable Loc : %d"), OwnThisEatable);

            double OwnOldEatable = FVector::Dist(OwnerLocation, PreviousClosestEatableLocation);
            UE_LOG(LogTemp, Display, TEXT("Distance between OwnerLocation and Old eatable Loc : %d"), OwnOldEatable);


            if (FVector::Dist(OwnerLocation, ThisEatableLocation) < FVector::Dist(OwnerLocation, PreviousClosestEatableLocation))
            {
                ChosenClosestEatableLocation = ThisEatableLocation;
                EatablePawn = Cast<AMinionCharacter>(MinionAI->GetPawn());
                FString EatableName = EatablePawn->GetName();
                UE_LOG(LogTemp, Error, TEXT("Line Of Sight to Eatable: %s"), *EatableName);
            }
            PreviousClosestEatableLocation = ChosenClosestEatableLocation;
        }      

    }

    

    UE_LOG(LogTemp, Warning, TEXT("Exit MinionAI loop"));
    
    FString ChosenEatVec = ChosenClosestEatableLocation.ToCompactString();
    UE_LOG(LogTemp, Error, TEXT("The returned chosen location: %s"), *ChosenEatVec);

            
    if (ChosenClosestEatableLocation.IsZero() == false && OwnerComp.GetAIOwner()->LineOfSightTo(EatablePawn))
    {
        UE_LOG(LogTemp, Display, TEXT("Setting Line of sight to eatable"));
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ChosenClosestEatableLocation);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(EatableActorKey.SelectedKeyName, EatablePawn);

    }else
    {
        UE_LOG(LogTemp, Error, TEXT("Clearing values of eatable"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        OwnerComp.GetBlackboardComponent()->ClearValue(EatableActorKey.SelectedKeyName);

    }
    
}

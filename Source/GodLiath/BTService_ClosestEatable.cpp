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

    FVector ChosenClosestEatableLocation;

    // Bool to say whether enemy location has been changed
    bool CheckForVectorChange = false;

    // Check over all the eatable actors and find the closest one.
    for (AMinionCharacter* MinionChar : TActorRange<AMinionCharacter>(GetWorld()))
    {                
        if (MinionChar->IsEatable() == true)
        {
            ThisEatableLocation = MinionChar->GetTransform().GetLocation();

            // If this eatable minion is closer or equal to the distance than the last then set that as the eatable.
            // Generalised with just needing line of sight to eatable as well.
            if (FVector::Dist(OwnerLocation, ThisEatableLocation) <= FVector::Dist(OwnerLocation, PreviousClosestEatableLocation) || OwnerComp.GetAIOwner()->LineOfSightTo(MinionChar))
            {
                ChosenClosestEatableLocation = ThisEatableLocation;
                CheckForVectorChange = true;
                EatablePawn = Cast<AMinionCharacter>(MinionChar);
                FString EatableName = EatablePawn->GetName();
            }
            PreviousClosestEatableLocation = ChosenClosestEatableLocation;
        }      
    }   

    // If a Eatable is detected and seen then set values of it's location and actor.
    if (CheckForVectorChange && OwnerComp.GetAIOwner()->LineOfSightTo(EatablePawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ChosenClosestEatableLocation);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(EatableActorKey.SelectedKeyName, EatablePawn);

    }else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        OwnerComp.GetBlackboardComponent()->ClearValue(EatableActorKey.SelectedKeyName);

    }
    
}

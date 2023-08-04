// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MinionCharacter.h"
#include "BTService_ClosestEatable.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API UBTService_ClosestEatable : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ClosestEatable();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// FVector ChosenClosestEatableLocation;

	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector EatableActorKey;

private:
	// TArray<FVector> MinionLocationArray;
	
	FVector OwnerLocation;
	AMinionCharacter* EatablePawn;

	FVector ThisEatableLocation;
	
	FVector PreviousClosestEatableLocation;
};

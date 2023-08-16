// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EnemyCharacter.h"
#include "BTService_ClosestEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API UBTService_ClosestEnemy : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ClosestEnemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// FVector ChosenClosestEatableLocation;

	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector EnemyActorKey;

private:
	// TArray<FVector> EnemyLocationArray;
	
	FVector OwnerLocation;
	AEnemyCharacter* EnemyPawn;

	FVector ThisEnemyLocation;
	
	FVector PreviousClosestEnemyLocation;

	// bool CheckForVectorChange;
	
};

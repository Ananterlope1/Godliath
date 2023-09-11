// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EnemyCharacter.h"
#include "BTService_ClosestEnemy.generated.h"

/**
 * 
 */

USTRUCT()
struct FActor_Dist         
{
 
    GENERATED_USTRUCT_BODY()
 
public:

    float distance = 0;  
    AActor* actor = NULL;   
    
};

UCLASS()
class GODLIATH_API UBTService_ClosestEnemy : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ClosestEnemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	static void Distance_Sort(UPARAM() TArray <AActor*> Array_To_Sort, UPARAM()AActor* From_Actor, bool Descending, TArray <FActor_Dist> &Sorted_Array);
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



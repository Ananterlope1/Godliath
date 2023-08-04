// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsEatableCloser.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API UBTService_IsEatableCloser : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_IsEatableCloser();

protected:

		/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector EnemyLocKey;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector PlayerLocKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FVector OwnerLocation;
	
};

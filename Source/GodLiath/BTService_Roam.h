// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Roam.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API UBTService_Roam : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_Roam();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};

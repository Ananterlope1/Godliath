// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BerserkAIController.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API ABerserkAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;


private:

	// UPROPERTY(EditAnywhere)
	// float AcceptanceRadius = 100;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviour;

};

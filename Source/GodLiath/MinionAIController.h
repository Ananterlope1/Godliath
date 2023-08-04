// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "MinionAIController.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API AMinionAIController : public AEnemyAIController
{
	GENERATED_BODY()
	
public:
	bool IsDead() const;

	bool IsEatable() const;

	void setIsEatable(bool AreEatable);
};

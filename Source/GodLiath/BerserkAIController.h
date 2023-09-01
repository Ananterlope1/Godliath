// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.h"
#include "BerserkAIController.generated.h"


/**
 * 
 */
UCLASS()
class GODLIATH_API ABerserkAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	bool IsDead() const override;
	bool IsTrueDead() const;
};

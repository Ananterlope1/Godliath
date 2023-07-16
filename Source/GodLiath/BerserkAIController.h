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

protected:
	virtual void BeginPlay() override;

};

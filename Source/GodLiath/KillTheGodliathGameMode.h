// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GodLiathGameModeBase.h"
#include "KillTheGodliathGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API AKillTheGodliathGameMode : public AGodLiathGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	
};

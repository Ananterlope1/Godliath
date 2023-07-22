// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MinionCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API AMinionCharacter : public AEnemyCharacter
{
	GENERATED_BODY()



public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
	bool IsEatable = false;

	UFUNCTION(BlueprintPure)
	bool IsDead();
	
};

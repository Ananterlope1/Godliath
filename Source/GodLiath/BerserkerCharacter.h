// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BerserkerCharacter.generated.h"

/**
 * 
 */
class AMeleeWeapon;

UCLASS()
class GODLIATH_API ABerserkerCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

// public:
// 	// Sets default values for this character's properties
// 	ABerserkerCharacter();

// protected:
// 	// Called when the game starts or when spawned
// 	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	
};

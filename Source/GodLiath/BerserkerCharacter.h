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

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Eat function
	bool Eat();
	
};

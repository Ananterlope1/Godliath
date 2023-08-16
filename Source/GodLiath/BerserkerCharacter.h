// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "BerserkerCharacter.generated.h"


/**
 * 
 */
class AMeleeWeapon;

UCLASS()
class GODLIATH_API ABerserkerCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Check if is dead
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	//Eat function
	void Eat();

	// Used when in capture zone to allow actual death.
	UPROPERTY(EditAnywhere)
	bool Eating = false;

	// Check if in capture/ killzone
	UFUNCTION(BlueprintPure)
	bool IsEating() const;

	// Used when in capture zone to allow actual death.
	UPROPERTY(EditAnywhere)
	bool TrueDeath = false;

	// Check if in capture/ killzone
	UFUNCTION(BlueprintPure)
	bool IsTrueDead() const;

private:

	UPROPERTY(EditAnywhere)
	float ResurrectDelay = 3;

	UPROPERTY(EditAnywhere)
	FVector EatingScale = FVector(1.2, 1.2, 1.2);

	FTimerHandle ResurrectTimer;

	void PlayResurrection();
	
};

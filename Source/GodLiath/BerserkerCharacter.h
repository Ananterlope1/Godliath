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

	UFUNCTION(BlueprintPure)
	bool SetTrueDead(bool TrueDeathValue);

	UFUNCTION()
	void PlayResurrection();

	UFUNCTION()
	void ScaleFromEating(float CurrentSpeed);

	virtual void SwingWeapon() override;

	UFUNCTION(BlueprintPure)
	float GetMaxDamage() const;

	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

private:

	float MaxSpeed = 1200;

	UPROPERTY(EditAnywhere)
	float ResurrectDelay = 3;

	UPROPERTY(EditAnywhere)
	FVector EatingScale = FVector(0.2, 0.2, 0.2);

	UPROPERTY(EditAnywhere)
	float ScalingEating = 1.1;

	// UPROPERTY(EditAnywhere)
	// FVector BossCaptureScale = FVector(4.1, 4.1, 4.1);

	// UPROPERTY(EditAnywhere)
	// FVector CargoOpenScale = FVector(1.8, 1.8, 1.8);

	FTimerHandle ResurrectTimer;	

	// UPROPERTY(EditAnywhere)
	// USoundBase* AttackSound;

	UPROPERTY(EditAnywhere)
	USoundBase* EatSound;

	UPROPERTY(EditAnywhere)
	UAnimMontage* EatingMontage;
	
};

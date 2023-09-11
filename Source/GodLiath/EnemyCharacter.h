// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AMeleeWeapon;

UCLASS()
class GODLIATH_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// UFUNCTION(BlueprintPure)
	// virtual bool IsDead() const;

	virtual void SwingWeapon();

	UPROPERTY(VisibleAnywhere)
	float Health = 1;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
	bool Eatable = false;	
	
	UFUNCTION(BlueprintPure)
	bool IsEatable();

	UFUNCTION(BlueprintPure)
	bool SetIsEatable(bool SetIsEatable);
	
	UParticleSystem* GetEatenEmitter();

	void SetRotationRate();
	
	UPROPERTY()
	AMeleeWeapon* MeleeWeapon;

	UPROPERTY(EditAnywhere)
	FRotator SmoothRotationRate = FRotator(0.0f,180.0f,0.0f);

	UPROPERTY(EditAnywhere)
	USoundBase* AttackSound;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;	

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMeleeWeapon> MeleeClass;

	UPROPERTY(EditAnywhere)
	UParticleSystem* EatenEmitter;

	

};

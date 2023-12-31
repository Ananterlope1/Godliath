// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class GODLIATH_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

	void SwingWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	USoundBase* SwingSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSoundEnemy;

	UPROPERTY(EditAnywhere)
	float MaxRange = 100;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	bool MeleeTrace(FHitResult& HitResult, FVector& ShotDirection);

	AController* GetOwnerController() const;

	void SetMaxRange(float NewMaxRange);
	float GetMaxRange();

	void SetDamage(float NewDamage);
	float GetDamage();
};

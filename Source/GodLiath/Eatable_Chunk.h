// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Eatable_Chunk.generated.h"

class UBoxComponent;

UCLASS()
class GODLIATH_API AEatable_Chunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEatable_Chunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* HitBox;

	/** called when something enters the Box component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	bool Eatable = true;	
	
	UFUNCTION(BlueprintPure)
	bool IsEatable();

	UFUNCTION(BlueprintPure)
	bool SetIsEatable(bool SetIsEatable);
	
	UParticleSystem* GetEatenEmitter();

private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* EatenEmitter;

};

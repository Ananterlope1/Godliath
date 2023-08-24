// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "RotatorComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODLIATH_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this component's properties
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover( UMover* Mover);

	UFUNCTION(BlueprintCallable)
	void SetRotator( URotatorComponent* Rotator);
	

private:

	UPROPERTY(EditAnywhere)
	FName UnlockingActorTag;

	UMover* Mover;

	URotatorComponent* Rotator;
	
	AActor* GetAcceptableActor() const;

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Narration_Trigger.generated.h"

class UBoxComponent;

UCLASS()
class GODLIATH_API ANarration_Trigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANarration_Trigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narration")
	FName NarrationTag="Normal";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narration")
	TSubclassOf<UUserWidget> WidgetTextClass;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* HitBox;

	/** called when something enters the sphere component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Narration")
	float NarrationTimer = 7;

	UFUNCTION()
	void CleanUpNarration(UUserWidget* TextWidget);

	FTimerHandle NarrationHandle;
	FTimerDelegate NarrationDelegate;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "GameFramework/Actor.h"




UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	// Possible extensions or uses:
	// Measure weight
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		
		// If wanting the pawn or actor to stay stuck to the moving object.
		// UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		// if (Component != nullptr)
		// {	
			
		// 	Component->SetSimulatePhysics(false);
		// 	Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			

		// }
		
        if (Mover != nullptr)
        {
            Mover->SetShouldMove(true);
        }else if (Rotator != nullptr)
        {
            Rotator->SetShouldMove(true);
			// UE_LOG(LogTemp, Warning, TEXT("Unlocking"));
        }        
		
		// UE_LOG(LogTemp, Warning, TEXT("Unlocking"));

	}else{
		
		if (Mover != nullptr)
        {
            Mover->SetShouldMove(false);
        }else if (Rotator != nullptr)
        {
            Rotator->SetShouldMove(false);
			// UE_LOG(LogTemp, Warning, TEXT("Locking"));
        }
		
		// UE_LOG(LogTemp, Warning, TEXT("Locking"));
	}

}

void UTriggerComponent::SetMover(UMover* NewMover)
{

	Mover = NewMover;

}

void UTriggerComponent::SetRotator(URotatorComponent* NewRotator)
{

	Rotator = NewRotator;

}

AActor* UTriggerComponent::GetAcceptableActor() const
{

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{

		//UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetActorNameOrLabel());
		if (Actor->ActorHasTag(UnlockingActorTag))
		{
			return Actor;
		}
	}

	return nullptr;

}

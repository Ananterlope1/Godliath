// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTag_OnScaleOverlapped.h"
#include "Components/BoxComponent.h"

// Sets default values
ASetTag_OnScaleOverlapped::ASetTag_OnScaleOverlapped()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Tag_Box"));

}

// Called when the game starts or when spawned
void ASetTag_OnScaleOverlapped::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetTag_OnScaleOverlapped::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* ToTagActor = GetAcceptableActor();

	if (ToTagActor != nullptr)
	{
		if (ToTagActor->GetActorScale().X > ScaleToAddTag)
		{
			ToTagActor->Tags.AddUnique(TagToAdd);
		}	
	}
	
}

AActor* ASetTag_OnScaleOverlapped::GetAcceptableActor() const
{

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{

		//UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetActorNameOrLabel());
		if (Actor->ActorHasTag(TagToCheckFor))
		{
			return Actor;
		}
	}

	return nullptr;

}
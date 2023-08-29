// Fill out your copyright notice in the Description page of Project Settings.


#include "Capture_Actor.h"
#include "Components/SphereComponent.h"
#include "BerserkerCharacter.h"

// Sets default values
ACapture_Actor::ACapture_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup overlap box
	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Capture_Sphere"));
	HitSphere->OnComponentBeginOverlap.AddDynamic(this, &ACapture_Actor::OnOverlapBegin);
	HitSphere->OnComponentEndOverlap.AddDynamic(this, &ACapture_Actor::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACapture_Actor::BeginPlay()
{ 
	Super::BeginPlay();
	
	
}

// Called every frame
void ACapture_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACapture_Actor::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABerserkerCharacter>())
	{
		UE_LOG(LogTemp, Error, TEXT("Test is berserker"));
		ABerserkerCharacter* OverlappedBerserker = Cast<ABerserkerCharacter>(OtherActor);
		OverlappedBerserker->SetTrueDead(true);
		UE_LOG(LogTemp, Warning, TEXT("Setting overlap to berserker to True"));
	}
	
	// TArray<AActor*> Actors;
	// GetOverlappingActors(Actors);

	// for (AActor* Actor : Actors)
	// {
	// 	//UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetActorNameOrLabel());
	// 	if (Actor->IsA<ABerserkerCharacter>())
	// 	{

	// 		ABerserkerCharacter* OverlappedBerserker = Cast<ABerserkerCharacter>(Actor);
	// 		OverlappedBerserker->SetTrueDead(true);
	// 		UE_LOG(LogTemp, Warning, TEXT("Setting overlap to berserker to True"));
	// 	}
	// }
}

void ACapture_Actor::OnOverlapEnd(class UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<ABerserkerCharacter>())
	{
		UE_LOG(LogTemp, Error, TEXT("Test is berserker leaving"));
		ABerserkerCharacter* OverlappedBerserker = Cast<ABerserkerCharacter>(OtherActor);
		OverlappedBerserker->SetTrueDead(false);
		UE_LOG(LogTemp, Warning, TEXT("Setting stop overlap to berserker to false"));
	}

	// TArray<AActor*> Actors;
	// GetOverlappingActors(Actors);

	// for (AActor* Actor : Actors)
	// {
	// 	//UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetActorNameOrLabel());
	// 	if (Actor->IsA<ABerserkerCharacter>())
	// 	{

	// 		ABerserkerCharacter* OverlappedBerserker = Cast<ABerserkerCharacter>(Actor);
	// 		OverlappedBerserker->SetTrueDead(false);
	// 		UE_LOG(LogTemp, Warning, TEXT("Setting stop overlap to berserker to false"));
	// 	}
	// }
}

AActor* ACapture_Actor::GetAcceptableActor() const
{

	// TArray<AActor*> Actors;
	// GetOverlappingActors(Actors);

	// for (AActor* Actor : Actors)
	// {

	// 	//UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetActorNameOrLabel());
	// 	if (Actor->IsA(ABerserkerCharacter))
	// 	{
	// 		return Actor;
	// 	}
	// }

	return nullptr;

}
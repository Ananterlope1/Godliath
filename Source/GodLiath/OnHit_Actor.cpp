// Fill out your copyright notice in the Description page of Project Settings.


#include "OnHit_Actor.h"
#include "Components/BoxComponent.h"

// Sets default values
AOnHit_Actor::AOnHit_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup overlap box
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	

}

// Called when the game starts or when spawned
void AOnHit_Actor::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentHit.AddDynamic(this, &AOnHit_Actor::OnHit);
	
}

// Called every frame
void AOnHit_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOnHit_Actor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT("The pipes are hit!"));
}

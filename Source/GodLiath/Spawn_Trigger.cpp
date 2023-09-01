// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn_Trigger.h"
#include "BerserkerCharacter.h"

// Sets default values
ASpawn_Trigger::ASpawn_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn_Box"));
	// HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawn_Trigger::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ASpawn_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawn_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void ASpawn_Trigger::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	FVector Location((-10841.0f,1806.0f,115.0f));
// 	FRotator Rotation(0.0f, 0.0f, 0.0f);
// 	FActorSpawnParameters SpawnInfo;
// 	GetWorld()->SpawnActor<ABerserkerCharacter>(Location, Rotation, SpawnInfo);
// 	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// }


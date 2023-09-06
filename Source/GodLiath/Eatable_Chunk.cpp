// Fill out your copyright notice in the Description page of Project Settings.


#include "Eatable_Chunk.h"
#include "BerserkerCharacter.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEatable_Chunk::AEatable_Chunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Eatable_Box"));
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AEatable_Chunk::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEatable_Chunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEatable_Chunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEatable_Chunk::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABerserkerCharacter>())
	{
		ABerserkerCharacter* Berserker = Cast<ABerserkerCharacter>(OtherActor);
		if (Berserker != nullptr)
		{		
			this->SetActorHiddenInGame(true);
			UE_LOG(LogTemp, Error, TEXT("Chunk Eating"));	
			Berserker->Eat();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EatenEmitter, this->GetActorLocation());
			this->Destroy();
		}
		
	}
	
}

bool AEatable_Chunk::IsEatable()
{
	return Eatable;
}

bool AEatable_Chunk::SetIsEatable(bool SetIsEatable)
{
	Eatable = SetIsEatable;
	return Eatable;	
}

UParticleSystem* AEatable_Chunk::GetEatenEmitter()
{
	return EatenEmitter;
}


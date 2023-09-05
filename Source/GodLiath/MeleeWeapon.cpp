// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMeleeWeapon::MeleeTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) 
		return false;	
	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);
	ShotDirection = -OwnerRotation.Vector();

	FVector End = OwnerLocation + OwnerRotation.Vector() * MaxRange;

	//Things for attack to ignore i.e. not hit itself
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	// DrawDebugLine(GetWorld(), OwnerLocation, End, FColor::Green, true, 30 );
	return GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController* AMeleeWeapon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) 
		return nullptr;
	return OwnerPawn->GetController();
}

void AMeleeWeapon::SetMaxRange(float NewMaxRange)
{
	MaxRange = NewMaxRange;
}

float AMeleeWeapon::GetMaxRange()
{
	return MaxRange;
}

void AMeleeWeapon::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

float AMeleeWeapon::GetDamage()
{
	return Damage;
}

void AMeleeWeapon::SwingWeapon()
{

	FHitResult HitResult;
	FVector SwingDirection;	
	bool bSuccess = MeleeTrace(HitResult, SwingDirection);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, SwingDirection.Rotation());		
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor != nullptr)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSoundEnemy, HitResult.Location, SwingDirection.Rotation());
			FPointDamageEvent DamageEvent(Damage, HitResult, SwingDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}
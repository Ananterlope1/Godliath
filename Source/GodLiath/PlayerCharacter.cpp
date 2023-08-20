// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GodLiathGameModeBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CharRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// SetRootComponent(CharRoot);

	// CharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	// CharMesh->SetupAttachment(CharRoot);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &APlayerCharacter::LookRightRate);
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);
	PlayerInputComponent -> BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent -> BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent -> BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &APlayerCharacter::SprintEnd);

}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	// UE_LOG(LogTemp, Warning, TEXT("Health Left: %f"), Health);

	if (IsDead())
	{

		AGodLiathGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGodLiathGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	
	
	return DamageToApply;

}

void APlayerCharacter::MoveForward(float AxisValue) 
{

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Shoot()
{
	Gun -> PullTrigger();
}

void APlayerCharacter::Dash()
{
	// For adding emitters and sound to dash
	TArray<UParticleSystemComponent*> SpawnedEmitters;

	SpawnedEmitters.Add(UGameplayStatics::SpawnEmitterAttached(JetpackEmitter, GetMesh(), TEXT("JetpackEmitter_L")));
	SpawnedEmitters.Add(UGameplayStatics::SpawnEmitterAttached(JetpackEmitter, GetMesh(), TEXT("JetpackEmitter_R")));

	UGameplayStatics::SpawnSoundAttached(JetpackSound, GetMesh(), TEXT("JetpackEmitter_L"));
	UGameplayStatics::SpawnSoundAttached(JetpackSound, GetMesh(), TEXT("JetpackEmitter_R"));

	// ShotDirection = -OwnerRotation.Vector();
	
	const FVector ForwardDirection = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDirection * DashDistance, true, true);
	FHitResult FloorHit = GetCharacterMovement()->CurrentFloor.HitResult;
	FVector NormalFloor = GetCharacterMovement()->CurrentFloor.HitResult.Normal;
	//Need to see why character moves really far suddenly sometimes and slides normally other times
	GetMovementComponent()->SlideAlongSurface(ForwardDirection * DashDistance, 1-FloorHit.Time, NormalFloor, FloorHit, true);
	if (DashMontage)
	{
		PlayAnimMontage(DashMontage, 1, NAME_None);
		
	}
	FTimerHandle EmitterHandle;
	FTimerDelegate DisableDelegate;
	DisableDelegate.BindUFunction( this, FName("EmitterDeactivate"), SpawnedEmitters);
	GetWorldTimerManager().SetTimer(EmitterHandle, DisableDelegate, EmitterDeactivateTimer, false);	
}

void APlayerCharacter::EmitterDeactivate(TArray<UParticleSystemComponent*> SpawnedEmitters)
{
	for (UParticleSystemComponent* Emitter : SpawnedEmitters)
	{
		if (Emitter)
		{
			Emitter->DeactivateImmediate();
		}		
	}	
}

void APlayerCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}



bool APlayerCharacter::IsDead() const
{	
	return Health <= 0;
}

float APlayerCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}



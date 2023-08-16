// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AIBehaviour != nullptr)
    {
        RunBehaviorTree(AIBehaviour);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());        
        
    }   

}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);   

}

bool AEnemyAIController::IsDead() const
{
    AEnemyAIController* ControlledCharacter = Cast<AEnemyAIController>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        // bool isBerserkerDead = ControlledCharacter->IsDead();
        // UE_LOG(LogTemp, Warning, TEXT("Berserker ControlledCharacter Is Dead? %s"), isBerserkerDead? TEXT("true") : TEXT("false"));
        
        return ControlledCharacter->IsDead();
    }

    return true;
}
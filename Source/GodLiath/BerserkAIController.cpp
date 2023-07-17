// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void ABerserkAIController::BeginPlay()
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
void ABerserkAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);   

}
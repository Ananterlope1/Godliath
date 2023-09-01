// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkAIController.h"
#include "BerserkerCharacter.h"


bool ABerserkAIController::IsDead() const
{
    ABerserkerCharacter* ControlledCharacter = Cast<ABerserkerCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        // bool isBerserkerDead = ControlledCharacter->IsDead();
        // UE_LOG(LogTemp, Warning, TEXT("Berserker ControlledCharacter Is Dead? %s"), isBerserkerDead? TEXT("true") : TEXT("false"));
        
        return ControlledCharacter->IsDead();
    }

    return true;
}

bool ABerserkAIController::IsTrueDead() const
{
    ABerserkerCharacter* ControlledCharacter = Cast<ABerserkerCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        // bool isBerserkerDead = ControlledCharacter->IsDead();
        // UE_LOG(LogTemp, Warning, TEXT("Berserker ControlledCharacter Is Dead? %s"), isBerserkerDead? TEXT("true") : TEXT("false"));
        
        return ControlledCharacter->IsTrueDead();
    }

    return true;
}

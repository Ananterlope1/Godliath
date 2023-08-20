// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAIController.h"
#include "MinionCharacter.h"


bool AMinionAIController::IsDead() const
{
    AMinionCharacter* ControlledCharacter = Cast<AMinionCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        // UE_LOG(LogTemp, Error, TEXT("Minion Controller checking if dead"));        
        return ControlledCharacter->IsDead();
    }

    return true;
}

bool AMinionAIController::IsEatable() const
{
    AMinionCharacter* ControlledCharacter = Cast<AMinionCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        // UE_LOG(LogTemp, Error, TEXT("Minion Controller checking if Eatable"));
        // bool EatableCheck = ControlledCharacter->IsEatable();
        // UE_LOG(LogTemp, Display, TEXT("Minion Controller is eatable: %s"), EatableCheck? TEXT("true") : TEXT("false"));
        return ControlledCharacter->IsEatable();
    }

    return true;
}

void AMinionAIController::setIsEatable(bool AreEatable)
{
    AMinionCharacter* ControlledCharacter = Cast<AMinionCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        // UE_LOG(LogTemp, Error, TEXT("Minion Controller setting if Eatable"));
        ControlledCharacter->SetIsEatable(AreEatable);
    }
}

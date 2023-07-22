// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAIController.h"
#include "MinionCharacter.h"


bool AMinionAIController::IsDead() const
{
    AMinionCharacter* ControlledCharacter = Cast<AMinionCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        
        return ControlledCharacter->IsDead();
    }

    return true;
}

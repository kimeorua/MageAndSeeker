// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BossCharacter.h"

UPawnUIComponent* ABossCharacter::GetPawnUIComponent() const
{
    return Super::GetPawnUIComponent();
}

UMonsterUIComponent* ABossCharacter::GetMonsterUIComponent() const
{
    return Super::GetMonsterUIComponent();
}

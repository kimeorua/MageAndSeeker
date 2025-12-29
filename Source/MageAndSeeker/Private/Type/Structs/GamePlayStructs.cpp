// Fill out your copyright notice in the Description page of Project Settings.


#include "Type/Structs/GamePlayStructs.h"

float FProjectileSpec::GetManaCost() const
{
    const float Rate = FMath::Max(ManaCostRate, 0.f);
    return -BaseManaCost * (1.0f + Rate);
}

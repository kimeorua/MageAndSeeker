// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "DebugHelper.h"

UMASBaseAttributeSet::UMASBaseAttributeSet()
{
	InitCurrentHP(1.0f);
	InitMaxHP(1.0f);
	InitAttackPower(1.0f);
	InitDefensivePower(1.0f);
}

void UMASBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetCurrentHPAttribute())
    {
        float NewHP = FMath::Clamp(GetCurrentHP(), 0.0f, GetMaxHP());
        SetCurrentHP(NewHP);

        if (NewHP <= 0.0f)
        {
            DebugHelper::Print("Character Is Dead");
        }
    }
    else if (Data.EvaluatedData.Attribute == GetAttackPowerAttribute())
    {
        SetAttackPower(FMath::Max(GetAttackPower(), 0.0f));
    }
    else if (Data.EvaluatedData.Attribute == GetDefensivePowerAttribute())
    {
        SetDefensivePower(FMath::Max(GetDefensivePower(), 0.0f));
    }
}
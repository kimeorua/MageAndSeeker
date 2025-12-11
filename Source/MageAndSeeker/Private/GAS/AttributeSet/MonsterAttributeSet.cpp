// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/MonsterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MageAndSeekerFunctionLibrary.h"

#include "DebugHelper.h"

UMonsterAttributeSet::UMonsterAttributeSet()
{
	InitFireResistance(0.0f);
	InitIceResistance(0.0f);
	InitLightningResistance(0.0f);
    InitLevel(1.0f);
}

void UMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetFireResistanceAttribute())
    {
        float NewFR = FMath::Clamp(GetFireResistance(), 0.0f, 20.0f);
        SetFireResistance(NewFR);
    }
    else if (Data.EvaluatedData.Attribute == GetIceResistanceAttribute())
    {
        float NewIR = FMath::Clamp(GetIceResistance(), 0.0f, 20.0f);
        SetIceResistance(NewIR);
    }
    else if (Data.EvaluatedData.Attribute == GetLightningResistanceAttribute())
    {
        float NewLR = FMath::Clamp(GetLightningResistance(), 0.0f, 20.0f);
        SetLightningResistance(NewLR);
    }
}
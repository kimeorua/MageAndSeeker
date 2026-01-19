// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MageAndSeekerFunctionLibrary.h"
#include "MageAndSeekerGameplayTag.h"

#include "DebugHelper.h"

UMASBaseAttributeSet::UMASBaseAttributeSet()
{
	InitCurrentHP(1.0f);
	InitMaxHP(1.0f);
	InitAttackPower(1.0f);
}

void UMASBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetMaxHPAttribute())
    {
        float NewMaxHP = GetMaxHP() <= 0 ? 100.0f : GetMaxHP();
        SetMaxHP(NewMaxHP);
    }

    else  if (Data.EvaluatedData.Attribute == GetCurrentHPAttribute())
    {
        float NewHP = FMath::Clamp(GetCurrentHP(), 0.0f, GetMaxHP());
        SetCurrentHP(NewHP);

        if (GetCurrentHP() <= 0.0f)
        {
            UMageAndSeekerFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), MageAndSeekerGameplayTag::Shared_Status_Dead);
        }
    }

    else if (Data.EvaluatedData.Attribute == GetAttackPowerAttribute())
    {
        SetAttackPower(FMath::Max(GetAttackPower(), 0.0f));
    }
}
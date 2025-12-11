// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/ArtifactAttributeSet.h"
#include "GameplayEffectExtension.h"

const float MAX_AP = 100.0f;
const float AP_CHARGE_PER_HIT = 5.0f;

UArtifactAttributeSet::UArtifactAttributeSet()
{
	InitCurrentAP(0.0f);
	InitMaxAP(MAX_AP);
	InitAPChargePerHit(AP_CHARGE_PER_HIT);
}

void UArtifactAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetCurrentAPAttribute())
    {
        float NewAP = FMath::Clamp(GetCurrentAP(), 0.0f, GetMaxAP());
        SetCurrentAP(NewAP);
    }
    else if (Data.EvaluatedData.Attribute == GetMaxAPAttribute())
    {
    }
    else if (Data.EvaluatedData.Attribute == GetAPChargePerHitAttribute())
    {
        SetAPChargePerHit(FMath::Max(GetAPChargePerHit(), AP_CHARGE_PER_HIT));
    }
}
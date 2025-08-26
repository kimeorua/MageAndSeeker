// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/ArtifactAttributeSet.h"
#include "GameplayEffectExtension.h"


UArtifactAttributeSet::UArtifactAttributeSet()
{
	InitCurrentAP(0.0f);
	InitMaxAP(100.0f);
	InitAPChargePerHit(1.0f);
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
        SetMaxAP(FMath::Max(GetMaxAP(), 1.0f));
    }
    else if (Data.EvaluatedData.Attribute == GetAPChargePerHitAttribute())
    {
        SetAPChargePerHit(FMath::Max(GetAPChargePerHit(), 1.0f));
    }
}
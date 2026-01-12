// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/GEC_RuneEffect_Dmage.h"
#include "GAS/AttributeSet/MonsterAttributeSet.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "MageAndSeekerGameplayTag.h"

#include "DebugHelper.h"

struct FRuneDamageCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentHP)
    DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
    DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance)
    DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)

    FRuneDamageCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMASBaseAttributeSet, CurrentHP, Target, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMonsterAttributeSet, FireResistance, Target, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMonsterAttributeSet, IceResistance, Target, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMonsterAttributeSet, LightningResistance, Target, true);
    }
};

static const FRuneDamageCapture& GetDamageCapture()
{
    static FRuneDamageCapture Statics;
    return Statics;
}

UGEC_RuneEffect_Dmage::UGEC_RuneEffect_Dmage()
{
    RelevantAttributesToCapture.Add(GetDamageCapture().CurrentHPDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().FireResistanceDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().IceResistanceDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().LightningResistanceDef);
}

void UGEC_RuneEffect_Dmage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    float Damage = Spec.GetSetByCallerMagnitude(MageAndSeekerGameplayTag::Shared_Data_Damage, false, 0.f);

    float FireResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().FireResistanceDef, EvaluateParameters, FireResistance);

    float IceResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().IceResistanceDef, EvaluateParameters, IceResistance);

    float LightningResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().LightningResistanceDef, EvaluateParameters, LightningResistance);

    float ResistanceMultiplier = 0.0f;

    FGameplayTagContainer DamageTypeTagContainer;
    Spec.GetAllAssetTags(DamageTypeTagContainer);

    if (DamageTypeTagContainer.HasTag(MageAndSeekerGameplayTag::Shared_DamageType_Fire))
    {
        ResistanceMultiplier = 1.f - (FireResistance * 0.01f);
    }
    else if (DamageTypeTagContainer.HasTag(MageAndSeekerGameplayTag::Shared_DamageType_Ice))
    {
        ResistanceMultiplier = 1.f - (IceResistance * 0.01f);
    }
    else if (DamageTypeTagContainer.HasTag(MageAndSeekerGameplayTag::Shared_DamageType_Lightning))
    {
        ResistanceMultiplier = 1.f - (LightningResistance * 0.01f);
    }

    float TotalDamage = Damage * ResistanceMultiplier;

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(FRuneDamageCapture().CurrentHPProperty, EGameplayModOp::Additive, -TotalDamage));
}

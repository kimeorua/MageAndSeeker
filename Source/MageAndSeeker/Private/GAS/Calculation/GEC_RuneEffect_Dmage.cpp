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

static const FRuneDamageCapture& GetRuneDamageCapture()
{
    static FRuneDamageCapture Statics;
    return Statics;
}

UGEC_RuneEffect_Dmage::UGEC_RuneEffect_Dmage()
{
    RelevantAttributesToCapture.Add(GetRuneDamageCapture().CurrentHPDef);
    RelevantAttributesToCapture.Add(GetRuneDamageCapture().FireResistanceDef);
    RelevantAttributesToCapture.Add(GetRuneDamageCapture().IceResistanceDef);
    RelevantAttributesToCapture.Add(GetRuneDamageCapture().LightningResistanceDef);
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
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRuneDamageCapture().FireResistanceDef, EvaluateParameters, FireResistance);

    float IceResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRuneDamageCapture().IceResistanceDef, EvaluateParameters, IceResistance);

    float LightningResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRuneDamageCapture().LightningResistanceDef, EvaluateParameters, LightningResistance);

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

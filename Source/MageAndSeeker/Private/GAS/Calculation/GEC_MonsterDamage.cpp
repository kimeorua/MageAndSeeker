// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/GEC_MonsterDamage.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "GAS/AttributeSet/MonsterAttributeSet.h"
#include "MageAndSeekerGameplayTag.h"

#include "DebugHelper.h"

struct FMonsterDamageCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentHP)
    DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
    DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance)
    DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)

    FMonsterDamageCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMASBaseAttributeSet, CurrentHP, Target, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMonsterAttributeSet, FireResistance, Target, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMonsterAttributeSet, IceResistance, Target, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMonsterAttributeSet, LightningResistance, Target, true);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UMASBaseAttributeSet, AttackPower, Source, true);
    }
};

static const FMonsterDamageCapture& GetDamageCapture()
{
    static FMonsterDamageCapture Statics;
    return Statics;
}

UGEC_MonsterDamage::UGEC_MonsterDamage()
{
    RelevantAttributesToCapture.Add(GetDamageCapture().CurrentHPDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().AttackPowerDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().FireResistanceDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().IceResistanceDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().LightningResistanceDef);
}

void UGEC_MonsterDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    float DamageRate = Spec.GetSetByCallerMagnitude(MageAndSeekerGameplayTag::Shared_Data_Damage, false, 0.f);

    float FireResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().FireResistanceDef, EvaluateParameters, FireResistance);

    float IceResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().IceResistanceDef, EvaluateParameters, IceResistance);

    float LightningResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().LightningResistanceDef, EvaluateParameters, LightningResistance);

    float BaseDamage = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackPowerDef, EvaluateParameters, BaseDamage);

    float Damage = BaseDamage + (BaseDamage * DamageRate);

    FGameplayTagContainer DamageTypeTagContainer;
    Spec.GetAllAssetTags(DamageTypeTagContainer);

    float FinalDamage;
    float ResistanceMultiplier;

    if (DamageTypeTagContainer.HasTag(MageAndSeekerGameplayTag::Shared_DamageType_Fire))
    {
        ResistanceMultiplier = 1.f - (FireResistance * 0.01f);
    }
    else if (DamageTypeTagContainer.HasTag(MageAndSeekerGameplayTag::Shared_DamageType_Ice))
    {
        ResistanceMultiplier = 1.f - (IceResistance * 0.01f);
    }
    else if(DamageTypeTagContainer.HasTag(MageAndSeekerGameplayTag::Shared_DamageType_Lightning))
    {
        ResistanceMultiplier = 1.f - (LightningResistance * 0.01f);
    }

    FinalDamage = Damage * ResistanceMultiplier;

    DebugHelper::Print("Damage", FinalDamage);

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(FMonsterDamageCapture().CurrentHPProperty, EGameplayModOp::Additive, -FinalDamage));
}

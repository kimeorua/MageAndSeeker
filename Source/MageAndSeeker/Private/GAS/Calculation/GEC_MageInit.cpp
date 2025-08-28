// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/GEC_MageInit.h"
#include "GAS/AttributeSet/MageAttributeSet.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"

void UGEC_MageInit::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float HPLevelValue = ExecutionParams.GetTargetAbilitySystemComponent()->GetNumericAttribute(UMageAttributeSet::GetHPLevelAttribute());
	float AttackLevelValue = ExecutionParams.GetTargetAbilitySystemComponent()->GetNumericAttribute(UMageAttributeSet::GetAttackLevelAttribute());

	const float MaxHP = 100 + HPLevelValue * 10;
	const float AttackPower = 30 + AttackLevelValue * 5;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMASBaseAttributeSet::GetMaxHPAttribute(), EGameplayModOp::Override, MaxHP));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMASBaseAttributeSet::GetCurrentHPAttribute(), EGameplayModOp::Override, MaxHP));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMASBaseAttributeSet::GetAttackPowerAttribute(), EGameplayModOp::Override, AttackPower));
}

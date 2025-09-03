// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/GEC_MageLevelInit.h"
#include "Subsystem/SaveLoadSubsystem.h"
#include "GAS/AttributeSet/MageAttributeSet.h"

void UGEC_MageLevelInit::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UWorld* World = ExecutionParams.GetTargetAbilitySystemComponent()->GetWorld();
	if (!World) { return; }

	if (USaveLoadSubsystem* SaveLoadSubsystem = World->GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		float HPLevelValue = SaveLoadSubsystem->GetHPLevel();
		float AttackLevelValue = SaveLoadSubsystem->GetAttackLevel();

		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMageAttributeSet::GetHPLevelAttribute(), EGameplayModOp::Override, HPLevelValue));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMageAttributeSet::GetAttackLevelAttribute(), EGameplayModOp::Override, AttackLevelValue));
	}
	else
	{
		return;
	}
}
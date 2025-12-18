// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/GEC_MageLevelInit.h"
#include "Subsystem/SaveLoadSubsystem.h"
#include "Type/Structs/SaveDataStructs.h"
#include "GAS/AttributeSet/MageAttributeSet.h"

#include "DebugHelper.h"

void UGEC_MageLevelInit::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UWorld* World = ExecutionParams.GetTargetAbilitySystemComponent()->GetWorld();
	if (!World) { return; }

	if (USaveLoadSubsystem* SaveLoadSubsystem = World->GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		FStatSaveData StatSaveData = SaveLoadSubsystem->CurrentSaveDataFromStat();

		float HPLevelValue = StatSaveData.HPLevel;
		float AttackLevelValue = StatSaveData.AttackLevel;

		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMageAttributeSet::GetHPLevelAttribute(), EGameplayModOp::Override, HPLevelValue));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMageAttributeSet::GetAttackLevelAttribute(), EGameplayModOp::Override, AttackLevelValue));
	}
	else
	{
		return;
	}
}
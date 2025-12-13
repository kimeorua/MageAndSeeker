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
		int32 Slot = SaveLoadSubsystem->GetCurrentSlotIndex();
		int32 HP_LV;
		int32 Attack_LV;

		float HPLevelValue = 0.f;
		float AttackLevelValue = 0.f;

		if (SaveLoadSubsystem->GetMageStat(Slot, HP_LV, Attack_LV))
		{
			HPLevelValue = HP_LV;
			AttackLevelValue = Attack_LV;
		}
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMageAttributeSet::GetHPLevelAttribute(), EGameplayModOp::Override, HPLevelValue));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMageAttributeSet::GetAttackLevelAttribute(), EGameplayModOp::Override, AttackLevelValue));
	}
	else
	{
		return;
	}
}
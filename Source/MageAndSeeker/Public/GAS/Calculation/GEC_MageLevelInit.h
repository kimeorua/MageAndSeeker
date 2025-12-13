// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_MageLevelInit.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UGEC_MageLevelInit : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
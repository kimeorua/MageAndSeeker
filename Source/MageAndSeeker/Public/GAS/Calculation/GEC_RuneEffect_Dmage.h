// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_RuneEffect_Dmage.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UGEC_RuneEffect_Dmage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEC_RuneEffect_Dmage();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};

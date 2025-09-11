// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "MASAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMASAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputRelased(const FGameplayTag& InInputTag);
};

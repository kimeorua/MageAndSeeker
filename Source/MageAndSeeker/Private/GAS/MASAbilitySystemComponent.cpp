// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MASAbilitySystemComponent.h"

#include "DebugHelper.h"

void UMASAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) { return; }
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) { continue; }

		TryActivateAbility(AbilitySpec.Handle);

		DebugHelper::Print("Ability Activate");
	}
}

void UMASAbilitySystemComponent::OnAbilityInputRelased(const FGameplayTag& InInputTag)
{
	DebugHelper::Print("Ability Deactivate");
}

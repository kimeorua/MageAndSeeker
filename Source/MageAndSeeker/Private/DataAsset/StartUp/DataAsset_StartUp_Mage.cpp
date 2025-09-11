// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUp/DataAsset_StartUp_Mage.h"
#include "GAS/Ability/MageGameplayAbility.h"
#include "GAS/MASAbilitySystemComponent.h"

void UDataAsset_StartUp_Mage::GiveToAbilitySystemComponent(UMASAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FMageAbilitySet& AbilitySet : MageAbilitySets)
	{
		if (!AbilitySet.IsVaild()) { continue; }

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
bool FMageAbilitySet::IsVaild() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
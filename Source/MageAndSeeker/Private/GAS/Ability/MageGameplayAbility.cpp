// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/MageGameplayAbility.h"
#include "Character/MageCharacter.h"

AMageCharacter* UMageGameplayAbility::GetMageCharacterFromActorInfo()
{
	if (!CachedMageCharacter.IsValid())
	{
		CachedMageCharacter = Cast<AMageCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedMageCharacter.IsValid() ? CachedMageCharacter.Get() : nullptr;
}

UMageCombatComponent* UMageGameplayAbility::GetMageCombatComponentFromActorInfo()
{
	return GetMageCharacterFromActorInfo()->GetMageCombatComponent();
}

UMageUIComponent* UMageGameplayAbility::GetMageUIComponentFromActorInfo()
{
	return GetMageCharacterFromActorInfo()->GetMageUIComponent();
}
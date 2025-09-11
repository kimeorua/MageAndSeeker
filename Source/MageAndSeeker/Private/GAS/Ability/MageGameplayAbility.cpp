// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/MageGameplayAbility.h"
#include "Character/MageCharacter.h"

AMageCharacter* UMageGameplayAbility::GetMageCharacterFromActorInfo()
{
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AMageCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr;
}

UMageWeaponComponent* UMageGameplayAbility::GetMageWeaponComponentFromActorInfo()
{
	return Cast<IWeaponInterface>(GetMageCharacterFromActorInfo())->GetMageWeaponComponent();
}
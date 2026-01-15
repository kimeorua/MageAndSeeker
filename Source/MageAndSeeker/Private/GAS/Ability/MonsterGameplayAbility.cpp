// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/MonsterGameplayAbility.h"
#include "Character/MonsterCharacter.h"

AMonsterCharacter* UMonsterGameplayAbility::GetMonsterCharacterFromActorInfo()
{
	if (!CachedMonsterCharacter.IsValid())
	{
		CachedMonsterCharacter = Cast<AMonsterCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedMonsterCharacter.IsValid() ? CachedMonsterCharacter.Get() : nullptr;
}

UMonsterUIComponent* UMonsterGameplayAbility::GetMonsterUIComponentFromActorInfo()
{
	return GetMonsterCharacterFromActorInfo()->GetMonsterUIComponent();
}
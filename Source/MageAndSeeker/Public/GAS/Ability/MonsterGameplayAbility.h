// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/MASGameplayAbility.h"
#include "MonsterGameplayAbility.generated.h"

class AMonsterCharacter;
class UMonsterUIComponent;

UCLASS()
class MAGEANDSEEKER_API UMonsterGameplayAbility : public UMASGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "MagicAndSeeker | Ability")
	AMonsterCharacter* GetMonsterCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "MagicAndSeeker | Ability")
	UMonsterUIComponent* GetMonsterUIComponentFromActorInfo();

private:
	TWeakObjectPtr<AMonsterCharacter> CachedMonsterCharacter;
};

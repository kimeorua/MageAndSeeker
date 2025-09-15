// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/MASGameplayAbility.h"
#include "MageGameplayAbility.generated.h"

class AMageCharacter;
class UMageWeaponComponent;
class UMageUIComponent;

UCLASS()
class MAGEANDSEEKER_API UMageGameplayAbility : public UMASGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "MagicAndSeeker | Ability")
	AMageCharacter* GetMageCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "MagicAndSeeker | Ability")
	UMageWeaponComponent* GetMageWeaponComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Wrroir | Ability")
	UMageUIComponent* GetMageUIComponentFromActorInfo();

private:
	TWeakObjectPtr<AMageCharacter> CachedWarriorHeroCharacter;
};

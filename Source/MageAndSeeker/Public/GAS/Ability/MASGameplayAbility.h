// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MASGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EMASAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class MAGEANDSEEKER_API UMASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "MageAndSeeker Ability")
	EMASAbilityActivationPolicy AbilityActivationPolicy = EMASAbilityActivationPolicy::OnTriggered;

	// ~Begin UAbilityInterface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~End UAbilityInterface
};

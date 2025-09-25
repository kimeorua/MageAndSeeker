// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MageAnimInstance.h"
#include "Character/MageCharacter.h"
#include "MageAndSeekerFunctionLibrary.h"
#include "MageAndSeekerGameplayTag.h"

void UMageAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningMageCharacter = Cast<AMageCharacter>(OwningCharacter);
	}
}

void UMageAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (OwningMageCharacter)
	{
		bIsCombat = UMageAndSeekerFunctionLibrary::NativeDoseActorHaveTag(OwningMageCharacter, MageAndSeekerGameplayTag::Mage_Status_CombatMode);
	}
}
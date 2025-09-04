// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MageAnimInstance.h"
#include "Character/MageCharacter.h"

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
}
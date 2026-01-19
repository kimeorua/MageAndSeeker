// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MonsterAnimInstance.h"
#include "Character/MonsterCharacter.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningMonsterCharacter = Cast<AMonsterCharacter>(OwningCharacter);
	}
}

void UMonsterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

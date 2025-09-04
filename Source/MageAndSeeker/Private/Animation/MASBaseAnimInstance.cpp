// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MASBaseAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UMASBaseAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		CharacterMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UMASBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !CharacterMovementComponent) { return; }

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = CharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
	LocomationDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}

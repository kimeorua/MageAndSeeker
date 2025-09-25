// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/MASBaseAnimInstance.h"
#include "MageAnimInstance.generated.h"

class AMageCharacter;

UCLASS()
class MAGEANDSEEKER_API UMageAnimInstance : public UMASBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrence")
	AMageCharacter* OwningMageCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrence")
	bool bIsCombat = false;
};

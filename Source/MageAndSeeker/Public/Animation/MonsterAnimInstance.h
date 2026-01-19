// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/MASBaseAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

class AMonsterCharacter;

UCLASS()
class MAGEANDSEEKER_API UMonsterAnimInstance : public UMASBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrence")
	AMonsterCharacter* OwningMonsterCharacter;
};

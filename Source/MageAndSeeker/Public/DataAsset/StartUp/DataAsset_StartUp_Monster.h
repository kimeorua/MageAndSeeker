// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUp/DataAsset_StartUp.h"
#include "DataAsset_StartUp_Monster.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UDataAsset_StartUp_Monster : public UDataAsset_StartUp
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UMASAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
};

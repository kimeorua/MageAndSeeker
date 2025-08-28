// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUp.generated.h"

class UMASAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class MAGEANDSEEKER_API UDataAsset_StartUp : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UMASAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUp Data")
	TArray < TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUp/DataAsset_StartUp.h"
#include "GameplayTagContainer.h"
#include "DataAsset_StartUp_Mage.generated.h"

class UMageGameplayAbility;

USTRUCT(BlueprintType)
struct FMageAbilitySet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMageGameplayAbility>AbilityToGrant;

	bool IsVaild() const;
};

UCLASS()
class MAGEANDSEEKER_API UDataAsset_StartUp_Mage : public UDataAsset_StartUp
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUp Data | Mage Ability", meta = (TitleProperty = "InputTag"))
	TArray<FMageAbilitySet>MageAbilitySets;

public:
	virtual void GiveToAbilitySystemComponent(UMASAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
};

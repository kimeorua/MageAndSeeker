// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "MASBaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MAGEANDSEEKER_API UMASBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CurrentHP;
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHP;
	UPROPERTY(BlueprintReadOnly, Category = "Attack Power", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackPower;
	UPROPERTY(BlueprintReadOnly, Category = "Defence Power", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData DefensivePower;

public:
	UMASBaseAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;

	ATTRIBUTE_ACCESSORS(UMASBaseAttributeSet, CurrentHP);
	ATTRIBUTE_ACCESSORS(UMASBaseAttributeSet, MaxHP);
	ATTRIBUTE_ACCESSORS(UMASBaseAttributeSet, AttackPower);
	ATTRIBUTE_ACCESSORS(UMASBaseAttributeSet, DefensivePower);
};
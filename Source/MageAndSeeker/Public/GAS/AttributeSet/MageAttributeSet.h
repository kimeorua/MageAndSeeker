// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "MageAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MAGEANDSEEKER_API UMageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData HPLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Attack Power", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CurrentMP;

	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMP;

public:
	UMageAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;

	ATTRIBUTE_ACCESSORS(UMageAttributeSet, HPLevel);
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, AttackLevel);
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, CurrentMP);
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, MaxMP);
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, MaxLevel);
};

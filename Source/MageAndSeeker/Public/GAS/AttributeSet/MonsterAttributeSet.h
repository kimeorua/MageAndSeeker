// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "MonsterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MAGEANDSEEKER_API UMonsterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData FireResistance;
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData IceResistance;
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData LightningResistance;
	UPROPERTY(BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Level;

public:
	UMonsterAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;

	ATTRIBUTE_ACCESSORS(UMonsterAttributeSet, FireResistance);
	ATTRIBUTE_ACCESSORS(UMonsterAttributeSet, IceResistance);
	ATTRIBUTE_ACCESSORS(UMonsterAttributeSet, LightningResistance);
	ATTRIBUTE_ACCESSORS(UMonsterAttributeSet, Level);
};

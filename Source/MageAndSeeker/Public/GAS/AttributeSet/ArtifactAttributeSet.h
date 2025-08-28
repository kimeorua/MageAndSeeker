// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "ArtifactAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MAGEANDSEEKER_API UArtifactAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Artifact", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CurrentAP;
	UPROPERTY(BlueprintReadOnly, Category = "Artifact", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAP;
	UPROPERTY(BlueprintReadOnly, Category = "Artifact", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData APChargePerHit;

public:
	UArtifactAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;

	ATTRIBUTE_ACCESSORS(UArtifactAttributeSet, CurrentAP);
	ATTRIBUTE_ACCESSORS(UArtifactAttributeSet, MaxAP);
	ATTRIBUTE_ACCESSORS(UArtifactAttributeSet, APChargePerHit);
};

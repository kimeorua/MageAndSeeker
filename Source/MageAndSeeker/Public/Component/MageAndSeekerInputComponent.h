// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "MageAndSeekerInputComponent.generated.h"

UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelaseddFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UMageAndSeekerInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("InputConfig Is Not Vaild"));

	if (UInputAction* FoundInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundInputAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UMageAndSeekerInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelaseddFunc)
{
	checkf(InInputConfig, TEXT("InputConfig Is Not Vaild"));

	for (const FMASInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputAction)
	{
		if (!AbilityInputActionConfig.IsVaild()) { continue; }
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
	}
}
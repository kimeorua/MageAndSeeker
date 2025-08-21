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

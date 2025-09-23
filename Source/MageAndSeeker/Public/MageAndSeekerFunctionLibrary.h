// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/MageAndSeekerEnum.h"
#include "MageAndSeekerGameplayTag.h"
#include "MageAndSeekerFunctionLibrary.generated.h"

class UMASAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EMASInputMode InInputMode);

	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library", meta = (WorldContext = "WorldContextObject"))
	static int32 GetCurrentCycle(const UObject* WorldContextObject);

	static UMASAbilitySystemComponent* NativeGetMageASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library")
	static void RemoveGameplayTagToActorIfFind(AActor* InActor, FGameplayTag TagToRemove);
};

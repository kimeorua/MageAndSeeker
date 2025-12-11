// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/Enums/FunctionLibraryEnums.h"
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

	static UMASAbilitySystemComponent* NativeGetMageASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library")
	static void RemoveGameplayTagToActorIfFind(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "MaginAndSeeker | Function Library", meta = (DisplayName = "Dose Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EMageAndSeekerConfirmType& OutConfirmType);

	UFUNCTION(BlueprintPure, Category = "Utility|Interface")
	static UPARAM(DisplayName = "Found Interface") TScriptInterface<IInterface> FindComponentByInterface(AActor* TargetActor, TSubclassOf<UInterface> InterfaceClass);
};

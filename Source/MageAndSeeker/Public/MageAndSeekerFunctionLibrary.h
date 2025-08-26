// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/MageAndSeekerEnum.h"
#include "MageAndSeekerFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TurnBasedGame | Function Library", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EMASInputMode InInputMode);

	UFUNCTION(BlueprintCallable, Category = "TurnBasedGame | Function Library", meta = (WorldContext = "WorldContextObject"))
	static int32 GetCurrentCycle(const UObject* WorldContextObject);
};

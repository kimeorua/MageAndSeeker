// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Type/Structs/GamePlayStructs.h"
#include "MagicRune.generated.h"

UCLASS(BlueprintType, Blueprintable)
class MAGEANDSEEKER_API UMagicRune : public UObject
{
	GENERATED_BODY()

public:
	void RuneInit(FRuneData Data);

	FRuneData GetRuneData() const { return RuneData; }

	UFUNCTION(BlueprintNativeEvent)
	FProjectileSpec RuneEffect(const FProjectileSpec& Spec);
	virtual FProjectileSpec RuneEffect_Implementation(const FProjectileSpec& Spec);
	
private:
	UPROPERTY(EditAnywhere, Category = "Data",  meta = (AllowPrivateAccess = "true"))
	FRuneData RuneData;
};
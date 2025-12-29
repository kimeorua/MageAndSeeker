// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Type/Enums/GamePlayEnums.h"
#include "GameplayTagContainer.h"
#include "GamePlayStructs.generated.h"

class UMagicRune;

USTRUCT(BlueprintType)
struct FBookData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EElementalType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BookLevel = 1;
};

USTRUCT(BlueprintType)
struct FRuneData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName RuneID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RuneLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERuneApplyType RuneApplyType;
};

USTRUCT(BlueprintType)
struct FRuneCreateData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName RuneID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RuneLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERuneApplyType RuneApplyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMagicRune>CreateRuneClass;

	bool operator==(const FRuneCreateData& Other) const
	{
		return RuneID == Other.RuneID && RuneLevel == Other.RuneLevel && RuneApplyType == Other.RuneApplyType;
	}
};


USTRUCT(BlueprintType)
struct FEquipedRunes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EElementalType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMagicRune*> EquipedRunes;
};

USTRUCT(BlueprintType)
struct FProjectileSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CastSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaCostRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer HitEventTags;

	static constexpr float BaseManaCost = 2.0f;

	float GetManaCost() const;
};
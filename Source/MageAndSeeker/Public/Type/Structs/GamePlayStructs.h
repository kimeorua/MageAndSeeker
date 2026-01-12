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

	FBookData() : Type(EElementalType::None), BookLevel(1) {}
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

	FRuneData() : RuneID(""), RuneLevel(1), RuneApplyType(ERuneApplyType::None) {}
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

	FRuneCreateData() : RuneID(""), RuneLevel(1), RuneApplyType(ERuneApplyType::None), CreateRuneClass(nullptr){}
};


USTRUCT(BlueprintType)
struct FEquipedRunes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EElementalType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMagicRune*> EquipedRunes;

	FEquipedRunes() : Type(EElementalType::None) {}
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
	float DamageRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float APChargeRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EffectableRuneLV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DamageTag;

	static constexpr float BaseManaCost = 2.0f;

	float GetManaCost() const;

	FProjectileSpec() : Count(1), Size(1.0f), ProjectileSpeed(1.0f), CastSpeed(1.0f), ManaCostRate(0.1f), DamageRate(0.1f), APChargeRate(0.1f), EffectableRuneLV(1), DamageTag(FGameplayTag::EmptyTag){}
};
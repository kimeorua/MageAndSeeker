// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SaveDataStructs.generated.h"

USTRUCT(BlueprintType)
struct FStatSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	int32 HPLevel = 0;

	UPROPERTY()
	int32 AttackLevel = 0;
};

USTRUCT(BlueprintType)
struct FBookLevelData
{
	GENERATED_BODY()

	UPROPERTY()
	int32 FireBookLevel = 1;

	UPROPERTY()
	int32 IceBookLevel  = 1;

	UPROPERTY()
	int32 LightningBookLevel  = 1;
};
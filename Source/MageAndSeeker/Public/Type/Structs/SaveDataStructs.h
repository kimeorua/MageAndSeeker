// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Type/Enums/GamePlayEnums.h"
#include "Type/Structs/GamePlayStructs.h"
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

USTRUCT(BlueprintType)
struct FSavedBookRuneData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FRuneCreateData> FireRuneData;

	UPROPERTY()
	TArray<FRuneCreateData> IceRuneData;

	UPROPERTY()
	TArray<FRuneCreateData> LightningRuneData;

	void AllEmpty()
	{
		FireRuneData.Empty();
		IceRuneData.Empty();
		LightningRuneData.Empty();
	}
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Type/Enums/GamePlayEnums.h"
#include "DataTableStructs.generated.h"

class UMagicRune;

USTRUCT(BlueprintType)
struct FMagicRuneDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName RuneID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName RuneName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMagicRuneType RuneType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERuneApplyType RuneApplyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMagicRune>MagicRune_BP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Type/MageAndSeekerEnum.h"
#include "MageAndSeekerStruct.generated.h"

USTRUCT(BlueprintType)
struct FBookData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BookLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBookType BookType = EBookType::Fire;
};
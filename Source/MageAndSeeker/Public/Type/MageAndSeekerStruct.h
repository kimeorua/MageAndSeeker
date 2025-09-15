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

    FBookData()
    {
        BookLevel = 1;
        BookType = EBookType::Fire;
    }

    FBookData(const FBookData& Other)
    {
        BookLevel = Other.BookLevel;
        BookType = Other.BookType;
    }

    FBookData& operator=(const FBookData& Other)
    {
        if (this != &Other) // 자기 자신 체크
        {
            BookLevel = Other.BookLevel;
            BookType = Other.BookType;
        }
        return *this;
    }
};
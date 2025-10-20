// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Type/MageAndSeekerEnum.h"
#include "MageAndSeekerStruct.generated.h"

class UBaseArtifact;

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

USTRUCT(BlueprintType)
struct FArtifactDataRow : public FTableRowBase
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ArtifactID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ArtifactName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ArtifactDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UBaseArtifact> ArtifactClass;
};
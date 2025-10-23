// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Type/MageAndSeekerEnum.h"
#include "MageAndSeekerStruct.generated.h"

class UMagicModule;

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
struct FArtifactData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ArtifactID = -1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 UpgradeLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText ArtifactName;

    FArtifactData()
    {
        ArtifactID = -1;
        UpgradeLevel = 1;
    }

    FArtifactData(const FArtifactData& Other)
    {
        ArtifactID = Other.ArtifactID;
        UpgradeLevel = Other.UpgradeLevel;
        ArtifactName = Other.ArtifactName;
    }

    FArtifactData& operator=(const FArtifactData& Other)
    {
        if (this != &Other) // 자기 자신 체크
        {
            ArtifactID = Other.ArtifactID;
            UpgradeLevel = Other.UpgradeLevel;
            ArtifactName = Other.ArtifactName;
        }
        return *this;
    }
};

USTRUCT(BlueprintType)
struct FMagicModuleData : public FTableRowBase
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ModuleID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ModuleName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EApplyPhase ApplyPhase;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UMagicModule> MagicModuleClass;
};
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
struct FMagicModuleDataTableRow : public FTableRowBase
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString LimitModulesID;
};

USTRUCT(BlueprintType)
struct FEquippedMagicModule
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ModuleID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ModuleLevel = 1;
};

USTRUCT(BlueprintType)
struct FInventoryMagicModule
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FEquippedMagicModule>InventoryModule;
};

USTRUCT(BlueprintType)
struct FMagicModules
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UMagicModule*> Modules;
};

USTRUCT(BlueprintType)
struct FModuleSaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EBookType Type;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ModuleID = "";

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 UpgradeLevel = 1;

    FModuleSaveData()
    {
        ModuleID = "";
        UpgradeLevel = 1;
        Type = EBookType::Fire;
    }

    FModuleSaveData(const FModuleSaveData& Other)
    {
        ModuleID = Other.ModuleID;
        UpgradeLevel = Other.UpgradeLevel;
        Type = Other.Type;
    }

    FModuleSaveData& operator=(const FModuleSaveData& Other)
    {
        if (this != &Other) // 자기 자신 체크
        {
            ModuleID = Other.ModuleID;
            UpgradeLevel = Other.UpgradeLevel;
            Type = Other.Type;
        }
        return *this;
    }
};

USTRUCT(BlueprintType)
struct FMagicOrbSpawnData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 OrbCount = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector OrbScale = FVector(1.0, 1.0, 1.0);
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed = 1500.0f;

    FMagicOrbSpawnData()
    {
        OrbCount = 1;
        OrbScale = FVector(1.0, 1.0, 1.0);
        Speed = 1500.0f;
    }
    FMagicOrbSpawnData(const FMagicOrbSpawnData& Other)
    {
        OrbCount = Other.OrbCount;
        OrbScale = Other.OrbScale;
        Speed = Other.Speed;
    }

    FMagicOrbSpawnData& operator=(const FMagicOrbSpawnData& Other)
    {
        if (this != &Other) // 자기 자신 체크
        {
            OrbCount = Other.OrbCount;
            OrbScale = Other.OrbScale;
            Speed = Other.Speed;
        }
        return *this;
    }
};
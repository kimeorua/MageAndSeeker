// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	None UMETA(DisplayName = "None"),
	Fire UMETA(DisplayName = "Fire"),
	Ice UMETA(DisplayName = "Ice"),
	Lightning UMETA(DisplayName = "Lightning"),
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMagicRuneType : uint8
{
	None UMETA(DisplayName = "None"),
	ProjectileSize UMETA(DisplayName = "ProjectileSize"),
	Artifact UMETA(DisplayName = "Artifact"),
	ProjectileCount UMETA(DisplayName = "ProjectileCount"),
	CastSpeed UMETA(DisplayName = "CastSpeed"),
	Hited UMETA(DisplayName = "Hited"),
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ERuneApplyType : uint8
{
	None UMETA(DisplayName = "None"),
	OnCast UMETA(DisplayName = "OnCast"),
	OnProjectileCreate UMETA(DisplayName = "OnProjectileCreate"),
	OnHited UMETA(DisplayName = "OnHited"),
	OnUseArtifact UMETA(DisplayName = "OnUseArtifact"),
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EDungeonOptionType : uint8
{
	Elemental UMETA(DisplayName = "Elemental"),
	DropItem UMETA(DisplayName = "DropItem"),
	MonsterLevel UMETA(DisplayName = "MonsterLevel")
};

UENUM(BlueprintType)
enum class EDungeonElemental : uint8
{
	Fire,
	Ice,
	Lightning
};

UENUM(BlueprintType)
enum class EDungeonDropItem : uint8
{
	BookMaterial,
	WeaponMaterial,
	ArtifactMaterial,
	Gold
};

UENUM(BlueprintType)
enum class EDungeonMonsterLevel : uint8
{
	Level1 = 0,
	Level2 = 1,
	Level3 = 2,
	Boss = 3
};
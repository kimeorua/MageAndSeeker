// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EMASInputMode : uint8
{
	GameOnly,
	UIOnly
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Staff,
	Book,
	Artifact,
	Monster
};

UENUM(BlueprintType)
enum class EBookType : uint8
{
	Fire UMETA(DisplayName = "Fire"),
	Ice UMETA(DisplayName = "Ice"),
	Lightning UMETA(DisplayName = "Lightning")
};

UENUM()
enum class EMageAndSeekerConfirmType : uint8
{
	Yes,
	No
};

UENUM(BlueprintType)
enum class EApplyPhase : uint8
{
	OnHit UMETA(DisplayName = "On Hit"),
	OnCast UMETA(DisplayName = "On Cast"),
	OnMake UMETA(DisplayName = "On Make"),
	OnArtifactActivate UMETA(DisplayName = "On Artifact Activate")
};

UENUM(BlueprintType)
enum class EMatterType : uint8
{
	MagicBook UMETA(DisplayName = "MagicBook"),
	Staff UMETA(DisplayName = "Staff"),
	Artifact UMETA(DisplayName = "Artifact"),
	Gold UMETA(DisplayName = "Gold")
};

UENUM(BlueprintType)
enum class EMonsterLV : uint8
{
	LV_1 UMETA(DisplayName = "1"),
	LV_2 UMETA(DisplayName = "2"),
	LV_3 UMETA(DisplayName = "3"), 
	LV_Boss UMETA(DisplayName = "Boss")
};
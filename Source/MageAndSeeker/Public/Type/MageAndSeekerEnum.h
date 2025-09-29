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

UENUM()
enum class EOrbSize : uint8
{
	Midium UMETA(DisplayName = "Midium"), 
	Small UMETA(DisplayName = "Small"), 
	Big UMETA(DisplayName = "Big"),
};
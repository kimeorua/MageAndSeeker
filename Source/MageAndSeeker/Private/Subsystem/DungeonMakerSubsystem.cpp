// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DungeonMakerSubsystem.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MageCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MageAndSeekerGameplayTag.h"
#include "Character/MonsterCharacter.h"
#include "Character/BaseCharacter.h"

#include "DebugHelper.h"

void UDungeonMakerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("UDungeonMakerSubsystem Init");
}

void UDungeonMakerSubsystem::Deinitialize()
{
}
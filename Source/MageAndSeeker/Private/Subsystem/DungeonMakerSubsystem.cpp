// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DungeonMakerSubsystem.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MageCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MageAndSeekerGameplayTag.h"

#include "DebugHelper.h"

void UDungeonMakerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("UDungeonMakerSubsystem Init");
}

void UDungeonMakerSubsystem::Deinitialize()
{
}

void UDungeonMakerSubsystem::MoveToDungeon()
{
	if (!StartPoint)
	{
		StartPoint = Cast<ATargetPoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass()));
	}

	AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Mage) { return; }

	Mage->SetActorLocationAndRotation(StartPoint->GetActorLocation(), StartPoint->GetActorQuat());

	FGameplayEventData Payload;
	Payload.Target = Mage;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Mage, MageAndSeekerGameplayTag::Mage_Event_ModeChange, Payload);
}
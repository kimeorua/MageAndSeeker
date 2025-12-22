// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DungeonMakerSubsystem.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MageCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MageAndSeekerGameplayTag.h"
#include "Character/MonsterCharacter.h"
#include "Character/BaseCharacter.h"
#include "Type/Structs/DataTableStructs.h"

#include "DebugHelper.h"

void UDungeonMakerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentStage = 4;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	CurrentMonsterCount = 0;

	DebugHelper::Print("UDungeonMakerSubsystem Init");
}

void UDungeonMakerSubsystem::Deinitialize()
{
}

void UDungeonMakerSubsystem::SpawnMonster(EDungeonElemental DungeonElemental, EDungeonDropItem DungeonDropItem, EDungeonMonsterLevel DungeonMonsterLevel)
{
	if (DungeonMonsterLevel == EDungeonMonsterLevel::Boss)
	{
		SpawnBossMonster(DungeonElemental);
	}
	else
	{
		SpawnNormalMonster(DungeonElemental);
		SpawnMatterMonster(DungeonDropItem);
	}
}

void UDungeonMakerSubsystem::MoveToDungeon()
{
	DungeonStartPoint = Cast<ATargetPoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass()));

	if (!DungeonStartPoint) { return; }

	AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Mage->TeleportTo(DungeonStartPoint->GetActorLocation(), DungeonStartPoint->GetActorRotation());

	FGameplayEventData Payload;
	Payload.Target = Mage;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Mage, MageAndSeekerGameplayTag::Mage_Event_ModeChange, Payload);
}

void UDungeonMakerSubsystem::SpawnNormalMonster(EDungeonElemental DungeonElemental)
{
	static const FString Context(TEXT("Monster Spawn Normal"));

	FName Stage(*FString::Printf(TEXT("Stage%d"), CurrentStage));
	FMonsterDataTable* FoundRow;
	TArray<FMonsterData> SpawnData;

	FoundRow = NormalMonsterTable->FindRow<FMonsterDataTable>(Stage, Context);
	SpawnData = FoundRow->MonsterArr;

	for (FMonsterData Data : SpawnData)
	{
		for (int i = 0; i < Data.SpwnNum; i++)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation[CurrentMonsterCount]);
			SpawnTransform.SetRotation(FRotator(0.f, 180.f, 0.f).Quaternion());

			AMonsterCharacter* SpawnMatterMonster = GetWorld()->SpawnActor<AMonsterCharacter>(Data.Monster_BP, SpawnTransform, SpawnParameters);
			CurrentMonsterCount++;
		}
	}
}

void UDungeonMakerSubsystem::SpawnMatterMonster(EDungeonDropItem DungeonDropItem)
{
	static const FString Context(TEXT("Monster Spawn Matter"));

	if (CurrentStage < 3) { return; }

	FName Stage(*FString::Printf(TEXT("Stage%d"), CurrentStage));
	FMonsterDataTable* FoundRow;
	TArray<FMonsterData> SpawnData;

	if (DungeonDropItem == EDungeonDropItem::Gold) { return; }

	if (DropItemMonsterTable.Contains(DungeonDropItem))
	{
		FoundRow = DropItemMonsterTable[DungeonDropItem]->FindRow<FMonsterDataTable>(Stage, Context);
		SpawnData = FoundRow->MonsterArr;
	}

	for (FMonsterData Data : SpawnData)
	{
		for (int i = 0; i < Data.SpwnNum; i++)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation[CurrentMonsterCount]);
			SpawnTransform.SetRotation(FRotator(0.f, 180.f, 0.f).Quaternion());

			AMonsterCharacter* SpawnMatterMonster = GetWorld()->SpawnActor<AMonsterCharacter>(Data.Monster_BP, SpawnTransform, SpawnParameters);
			CurrentMonsterCount++;
		}
	}
}

void UDungeonMakerSubsystem::SpawnBossMonster(EDungeonElemental DungeonElemental)
{
	static const FString Context(TEXT("Monster Spawn Boss"));

	FName Stage;
	FMonsterDataTable* FoundRow;
	TArray<FMonsterData> SpawnData;

	switch (DungeonElemental)
	{
	case EDungeonElemental::Fire:
		Stage = "FireBoss";
		break;
	case EDungeonElemental::Ice:
		Stage = "IceBoss";
		break;
	case EDungeonElemental::Lightning:
		Stage = "LightningBoss";
		break;
	default:
		break;
	}

	FoundRow = BossMonsterTable->FindRow<FMonsterDataTable>(Stage, Context);
	SpawnData = FoundRow->MonsterArr;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(BossSpawnLocation);
	SpawnTransform.SetRotation(FRotator(0.f, 180.f, 0.f).Quaternion());

	AMonsterCharacter* SpawnBoss = GetWorld()->SpawnActor<AMonsterCharacter>(SpawnData[0].Monster_BP, SpawnTransform, SpawnParameters);

	CurrentMonsterCount++;
}
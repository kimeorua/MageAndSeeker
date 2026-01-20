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
#include "GameFramework/PlayerStart.h"

#include "DebugHelper.h"

void UDungeonMakerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentStage = 1;
	SpawnParameters = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	CurrentMonsterCount = 0;

	DebugHelper::Print("UDungeonMakerSubsystem Init");
}

void UDungeonMakerSubsystem::Deinitialize()
{
}

void UDungeonMakerSubsystem::SpawnMonster(EDungeonElemental DungeonElemental, EDungeonDropItem DungeonDropItem, EDungeonMonsterLevel DungeonMonsterLevel)
{
	DungeonInit(DungeonMonsterLevel);

	DungeonCreateData.InitDungeonCreateData(DungeonElemental, DungeonDropItem, DungeonMonsterLevel);

	if (DungeonMonsterLevel == EDungeonMonsterLevel::Boss)
	{
		SpawnBossMonster(DungeonElemental);
	}
	else
	{
		SpawnNormalMonster(DungeonElemental, DungeonMonsterLevel);
		SpawnMatterMonster(DungeonDropItem, DungeonMonsterLevel);
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

	GetWorld()->GetTimerManager().ClearTimer(DelayTimer);
}

void UDungeonMakerSubsystem::MonsterCountCheck()
{
	CurrentMonsterCount = FMath::Max(CurrentMonsterCount - 1, 0);

	if (CurrentMonsterCount <= 0)
	{
		if (CurrentStage < MaxStageCount)
		{
			CurrentStage++;

			GetWorld()->GetTimerManager().SetTimer(DelayTimer,[this]()
				{
					SpawnNormalMonster(DungeonCreateData.DungeonElemental, DungeonCreateData.DungeonMonsterLevel);
					SpawnMatterMonster(DungeonCreateData.DungeonDropItem, DungeonCreateData.DungeonMonsterLevel);
				},
				0.5f,
				false
			);
		}
		else
		{
			DungeonClear();
		}
	}
}

void UDungeonMakerSubsystem::SpawnNormalMonster(EDungeonElemental DungeonElemental, EDungeonMonsterLevel DungeonMonsterLevel)
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

			AMonsterCharacter* SpawnNormalMonster = GetWorld()->SpawnActorDeferred<AMonsterCharacter>(Data.Monster_BP, SpawnTransform, nullptr, nullptr, SpawnParameters);
			SpawnNormalMonster->SetMonsterLV(static_cast<int32>(DungeonMonsterLevel) + 1);
			SpawnNormalMonster->FinishSpawning(SpawnTransform);
			SpawnNormalMonster->SettingMonsterColor(DungeonElemental);
			CurrentMonsterCount++;
		}
	}
}

void UDungeonMakerSubsystem::SpawnMatterMonster(EDungeonDropItem DungeonDropItem, EDungeonMonsterLevel DungeonMonsterLevel)
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

			AMonsterCharacter* SpawnMatterMonster = GetWorld()->SpawnActorDeferred<AMonsterCharacter>(Data.Monster_BP, SpawnTransform, nullptr, nullptr, SpawnParameters);
			SpawnMatterMonster->SetMonsterLV(static_cast<int32>(DungeonMonsterLevel) + 1);
			SpawnMatterMonster->FinishSpawning(SpawnTransform);
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

	AMonsterCharacter* SpawnMatterMonster = GetWorld()->SpawnActorDeferred<AMonsterCharacter>(SpawnData[0].Monster_BP, SpawnTransform, nullptr, nullptr, SpawnParameters);
	SpawnMatterMonster->SetMonsterLV();
	SpawnMatterMonster->FinishSpawning(SpawnTransform);
	CurrentMonsterCount++;
}

void UDungeonMakerSubsystem::DungeonInit(EDungeonMonsterLevel DungeonMonsterLevel)
{
	switch (DungeonMonsterLevel)
	{
	case EDungeonMonsterLevel::Level1:
		MaxStageCount = 3;
		break;
	case EDungeonMonsterLevel::Level2:
		MaxStageCount = 5;
		break;
	case EDungeonMonsterLevel::Level3:
		MaxStageCount = 7;
		break;
	case EDungeonMonsterLevel::Boss:
		MaxStageCount = 1;
		break;
	default:
		break;
	}
}

void UDungeonMakerSubsystem::DungeonClear()
{
	DebugHelper::Print("Clear!!");
	MovePlayerToStartPoint();
	// TODO : 던전 클리어 UI 출력하기.
}


void UDungeonMakerSubsystem::MovePlayerToStartPoint()
{
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerStart* StartPoint = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	if (!StartPoint) { return; }

	AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Mage->TeleportTo(StartPoint->GetActorLocation(), StartPoint->GetActorRotation());

	FGameplayEventData Payload;
	Payload.Target = Mage;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Mage, MageAndSeekerGameplayTag::Mage_Event_ModeChange, Payload);
}
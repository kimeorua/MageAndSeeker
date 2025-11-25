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

void UDungeonMakerSubsystem::CreateMonsters(EBookType ElementalType, EMatterType Matter, EMonsterLV LV)
{
	DungeonElemental = ElementalType;
	DungeonLV = LV;
	DungeonMatter = Matter;

	switch (LV)
	{
	case EMonsterLV::LV_1:
		MaxStage = 3;
		break;
	case EMonsterLV::LV_2:
		MaxStage = 5;
		break;
	case EMonsterLV::LV_3:
		MaxStage = 7;
		break;
	case EMonsterLV::LV_Boss:
		MaxStage = 1;
		break;
	default:
		break;
	}

	if (LV == EMonsterLV::LV_Boss)
	{
		switch (ElementalType)
		{
		case EBookType::Fire:
			SpawnBossFromTable(FName("FireBoss"));
			break;
		case EBookType::Ice:
			SpawnBossFromTable(FName("IceBoss"));
			break;
		case EBookType::Lightning:
			SpawnBossFromTable(FName("LightningBoss"));
			break;
		default:
			break;
		}
	}
	else
	{
		SpawnBasicMonsterFromTable(ElementalType);
		SpawnMatterMonsterFromTable(MatterMonsterDataTable[Matter]);
	}
}

void UDungeonMakerSubsystem::OnMonsterDied()
{
	CurrentMonsterCount--;
	if (CurrentMonsterCount == 0)
	{
		if (StageCount == MaxStage)
		{
			DebugHelper::Print("Dungen End!");
		}
		else
		{
			FTimerHandle SpawnTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					StageCount++;
					CreateMonsters(DungeonElemental, DungeonMatter, DungeonLV);

					GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
				}), 2.0f, false); 
			
		}
	}
}

void UDungeonMakerSubsystem::SpawnBasicMonsterFromTable(EBookType ElementalType)
{
	static const FString ContextString(TEXT("Spawn Data Context"));
	FString RowString = "Stage" + FString::FromInt(StageCount);
	FName StageName = FName(*RowString);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FBasicMonsterDataTable* Row = BasicMonsterDataTable->FindRow<FBasicMonsterDataTable>(StageName, ContextString);
	if (Row)
	{
		for (FMonsyterCreateData Data : Row->StageMonsterArr)
		{
			for (int i = 0; i < Data.SpawnNum; i++)
			{
				CurrentMonsterCount++;
				FString MonsterRowString = "Point" + FString::FromInt(CurrentMonsterCount);
				FName SpawnPoint = FName(*MonsterRowString);

				FMonsterSpawnLocationDataTable* SpawnLocationRow = MonsterSpawnTable->FindRow<FMonsterSpawnLocationDataTable>(
					SpawnPoint, 
					ContextString
				);
		
				AMonsterCharacter* SpawnedMonster = GetWorld()->SpawnActor<AMonsterCharacter>(
					Data.MonsterBP, 
					SpawnLocationRow->SpawnLocation, 
					FRotator::ZeroRotator, 
					Params
				);
				SpawnedMonster->SettingElemental(ElementalType);
			}
		}
	}
}

void UDungeonMakerSubsystem::SpawnMatterMonsterFromTable(UDataTable* Table)
{
	static const FString ContextString(TEXT("Spawn Data Context"));

	if (StageCount < 3) { return; }

	FString RowString = "Stage" + FString::FromInt(StageCount);
	FName StageName = FName(*RowString);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FMatterMonsterDataTable* Row = Table->FindRow<FMatterMonsterDataTable>(StageName, ContextString);
	if (Row)
	{
		for (int i = 0; i <  Row->MatterMonster.SpawnNum; i++)
		{
			CurrentMonsterCount++;
			FString MonsterRowString = "Point" + FString::FromInt(CurrentMonsterCount);
			FName SpawnPoint = FName(*MonsterRowString);

			FMonsterSpawnLocationDataTable* SpawnLocationRow = MonsterSpawnTable->FindRow<FMonsterSpawnLocationDataTable>(
				SpawnPoint,
				ContextString
			);

			AMonsterCharacter* SpawnedMonster = GetWorld()->SpawnActor<AMonsterCharacter>(
				Row->MatterMonster.MonsterBP,
				SpawnLocationRow->SpawnLocation,
				FRotator::ZeroRotator,
				Params
			);
		}
	}
}

void UDungeonMakerSubsystem::SpawnBossFromTable(FName TableRowName)
{
	static const FString ContextString(TEXT("Spawn Data Context"));

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FBossMonsterDataTable* Row = BossMonsterDataTable->FindRow<FBossMonsterDataTable>(TableRowName, ContextString);
	
	FMonsterSpawnLocationDataTable* SpawnLocationRow = MonsterSpawnTable->FindRow<FMonsterSpawnLocationDataTable>(FName("BossPoint"), ContextString);
	ABaseCharacter* SpawnedMonster = GetWorld()->SpawnActor<ABaseCharacter>(
		Row->BossBP,
		SpawnLocationRow->SpawnLocation,
		FRotator::ZeroRotator,
		Params
	);
	CurrentMonsterCount++;
}
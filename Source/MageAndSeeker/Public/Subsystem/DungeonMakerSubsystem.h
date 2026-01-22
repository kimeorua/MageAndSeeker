// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/Enums/GamePlayEnums.h"
#include "DungeonMakerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdawnStart);

USTRUCT(BlueprintType)
struct FDungeonCreateData
{
	GENERATED_BODY()

	UPROPERTY()
	EDungeonElemental DungeonElemental;

	UPROPERTY()
	EDungeonDropItem DungeonDropItem;

	UPROPERTY()
	EDungeonMonsterLevel DungeonMonsterLevel;

	void InitDungeonCreateData(EDungeonElemental Elemental, EDungeonDropItem DropItem, EDungeonMonsterLevel MonsterLevel)
	{
		DungeonElemental = Elemental;
		DungeonDropItem = DropItem;
		DungeonMonsterLevel = MonsterLevel;
	}

	FDungeonCreateData() : DungeonElemental(EDungeonElemental::Fire), DungeonDropItem(EDungeonDropItem::BookMaterial), DungeonMonsterLevel(EDungeonMonsterLevel::Level1) {}
};

class ATargetPoint;

UCLASS(Abstract, Blueprintable)
class MAGEANDSEEKER_API UDungeonMakerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void SpawnMonster(EDungeonElemental DungeonElemental, EDungeonDropItem DungeonDropItem, EDungeonMonsterLevel DungeonMonsterLevel);
	void MoveToDungeon();

	UFUNCTION(BlueprintCallable)
	void MonsterCountCheck();

	UFUNCTION(BlueprintCallable)
	void SpawnNextStage();

	UPROPERTY()
	FOnCountdawnStart OnCountdawnStart;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Monster Spawn Table", meta = (AllowPrivateAccess = "true"))
	UDataTable* NormalMonsterTable;

	UPROPERTY(EditDefaultsOnly, Category = "Monster Spawn Table", meta = (AllowPrivateAccess = "true"))
	UDataTable* BossMonsterTable;

	UPROPERTY(EditDefaultsOnly, Category = "Monster Spawn Table", meta = (AllowPrivateAccess = "true"))
	TMap<EDungeonDropItem, UDataTable*> DropItemMonsterTable;

	UPROPERTY(EditDefaultsOnly, Category = "Monster Spawn Table", meta = (AllowPrivateAccess = "true"))
	TArray<FVector>SpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Monster Spawn Table", meta = (AllowPrivateAccess = "true"))
	FVector BossSpawnLocation;

	void SpawnNormalMonster(EDungeonElemental DungeonElemental, EDungeonMonsterLevel DungeonMonsterLevel);

	void SpawnMatterMonster(EDungeonDropItem DungeonDropItem, EDungeonMonsterLevel DungeonMonsterLevel);

	void SpawnBossMonster(EDungeonElemental DungeonElemental);

	void DungeonInit(EDungeonMonsterLevel DungeonMonsterLevel);

	void DungeonClear();

	void MovePlayerToStartPoint();

	int32 MaxStageCount;

	int32 CurrentStage;

	int32 CurrentMonsterCount;

	ESpawnActorCollisionHandlingMethod SpawnParameters;

	UPROPERTY()
	FDungeonCreateData DungeonCreateData;

	UPROPERTY()
	ATargetPoint* DungeonStartPoint;
};
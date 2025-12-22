// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/Enums/GamePlayEnums.h"
#include "DungeonMakerSubsystem.generated.h"

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

	void SpawnNormalMonster(EDungeonElemental DungeonElemental);

	void SpawnMatterMonster(EDungeonDropItem DungeonDropItem);

	void SpawnBossMonster(EDungeonElemental DungeonElemental);

	int32 CurrentStage;

	int32 CurrentMonsterCount;

	FActorSpawnParameters SpawnParameters;

	UPROPERTY()
	ATargetPoint* DungeonStartPoint;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/MageAndSeekerStruct.h"
#include "DungeonMakerSubsystem.generated.h"

class ATargetPoint;

UCLASS(Abstract, Blueprintable)
class MAGEANDSEEKER_API UDungeonMakerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
#pragma region Basic
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void MoveToDungeon();

	UFUNCTION(BlueprintCallable)
	void CreateMonsters(EBookType ElementalType, EMatterType Matter, EMonsterLV LV);
#pragma endregion

private:
	UPROPERTY()
	ATargetPoint* StartPoint;

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* BossMonsterDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* BasicMonsterDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	TMap<EMatterType, UDataTable*> MatterMonsterDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* MonsterSpawnTable;

	UPROPERTY()
	int32 CurrentMonsterCount = 0;

	UPROPERTY()
	int32 StageCount = 1;

	void SpawnBasicMonsterFromTable(EBookType ElementalType);
	void SpawnMatterMonsterFromTable(UDataTable* Table);
	void SpawnBossFromTable(FName TableRowName);
};

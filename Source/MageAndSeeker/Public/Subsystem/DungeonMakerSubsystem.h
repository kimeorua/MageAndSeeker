// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/MageAndSeekerEnum.h"
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

	UPROPERTY(EditAnywhere, Category = "Module", meta = (AllowPrivateAccess = "true"))
	UDataTable* BossMonsterDataTable;

	UPROPERTY(EditAnywhere, Category = "Module", meta = (AllowPrivateAccess = "true"))
	UDataTable* BasicMonsterDataTable;

	UPROPERTY(EditAnywhere, Category = "Module", meta = (AllowPrivateAccess = "true"))
	TMap<EMatterType, UDataTable*> MatterMonsterDataTable;
};

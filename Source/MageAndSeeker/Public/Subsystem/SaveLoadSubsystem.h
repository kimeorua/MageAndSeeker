// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/Structs/SaveDataStructs.h"
#include "SaveLoadSubsystem.generated.h"

class UMageAndSeekerSaveGame;

UCLASS()
class MAGEANDSEEKER_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SaveGameAsync(const int32 SlotNum, bool bIsNewGame, AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void LoadGameAsync(const int32 SlotNum, AActor* TargetActor);

	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSlotIndex(const int32 Slot)  { SlotIndex = Slot; }

	UFUNCTION(BlueprintCallable)
	bool GetMageStatFromSlot(int32 SaveSlot, int32& OutHPLevel,int32& OutAttackLevel);

	FStatSaveData CurrentSaveDataFromStat() const;

private:
	UPROPERTY()
	UMageAndSeekerSaveGame* CurrentSaveGame;

	UPROPERTY()
	int32 SlotIndex;

	UFUNCTION()
	void OnSaveCompleted(const FString& SlotName, int32 UserIndex, bool bSuccess);

	void CollectSaveData(AActor* TargetActor, UMageAndSeekerSaveGame* SaveGame);
	void ApplyLoadData(AActor* TargetActor, UMageAndSeekerSaveGame* SaveGame);

	void MakeNewGame();
};
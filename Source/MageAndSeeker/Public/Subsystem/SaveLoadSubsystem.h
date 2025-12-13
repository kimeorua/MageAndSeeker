// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
	void SaveGameAsync(const int32 SlotNum, bool bIsNewGame);

	UFUNCTION(BlueprintCallable)
	void LoadGameAsync(const int32 SlotNum);

	UFUNCTION(BlueprintPure)
	bool GetMageStat(int32 Slot, int32& HPLevel, int32& AttackLevel);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentSlotIndex() const { return CurrentSlotIndex; }

private:
	UPROPERTY()
	UMageAndSeekerSaveGame* CurrentSaveGame;

	int32 CurrentSlotIndex;

	void CollectStatData(bool IsNew);

	UFUNCTION()
	void OnSaveCompleted(const FString& SlotName, int32 UserIndex, bool bSuccess);

	UFUNCTION()
	void OnLoadCompleted(const FString& SlotName, int32 UserIndex, USaveGame* LoadedGame);
};
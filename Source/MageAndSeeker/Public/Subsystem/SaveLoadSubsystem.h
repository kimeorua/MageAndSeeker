// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/MageAndSeekerEnum.h"
#include "Type/MageAndSeekerStruct.h"
#include "SaveLoadSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinshedSvaeGameDelegate);

UCLASS()
class MAGEANDSEEKER_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SaveGame(int32 Slot, bool bIsNewGame);

	UFUNCTION(BlueprintCallable)
	void LoadGame(int32 Slot);

	UFUNCTION(BlueprintPure)
	bool GetSaveInfo(int32 Slot, FString& CycleInfo, FString& HPLV, FString& AttackLV);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentSaveSloat() const { return CurrentSlot; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentCycle() const { return CurrentCycle; }

	FORCEINLINE int32 GetHPLevel() const { return HPLevel; }

	FORCEINLINE int32 GetAttackLevel() const { return AttackLevel; }

	UFUNCTION()
	void OnSaveGameCompleted(const FString& SlotName, int32 SlotNum, bool bSuccess);

	UPROPERTY(BlueprintAssignable)
	FOnFinshedSvaeGameDelegate OnFinshedSvaeGame;

	FBookData GetLoadedBookData(EBookType BookType);

private:
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 CurrentCycle = 1;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float HPLevel = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float AttackLevel = 0;

	UPROPERTY()
	int32 CurrentSlot = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<EBookType, FBookData> BookDatas;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/MageAndSeekerEnum.h"
#include "Type/MageAndSeekerStruct.h"
#include "SaveLoadSubsystem.generated.h"

class UBaseArtifact;
class UMageAndSeekerSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinshedSvaeGameDelegate);

UCLASS()
class MAGEANDSEEKER_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
#pragma region Basic
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
#pragma endregion


#pragma region Save&Load
public:
	UFUNCTION(BlueprintCallable)
	void SaveGame(int32 Slot, bool bIsNewGame);

	UFUNCTION(BlueprintCallable)
	void LoadGame(int32 Slot);

	FBookData GetLoadedBookData(EBookType BookType);

#pragma endregion

#pragma region GetFunc
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentSaveSloat() const { return CurrentSlot; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentCycle() const { return CurrentCycle; }

	FORCEINLINE int32 GetHPLevel() const { return HPLevel; }

	FORCEINLINE int32 GetAttackLevel() const { return AttackLevel; }

	FORCEINLINE TMap<int32, FArtifactData> GetSavedArtifactInventory() const { return SavedArtifactInventory; }
	FORCEINLINE FArtifactData GetEquipedArtifactData() const { return EquipedArtifactData; }

	FORCEINLINE TArray<FModuleSaveData>GetSavedEquipedModule() const { return SavedEquipedModule; }

	UFUNCTION(BlueprintPure)
	bool GetSaveInfo(int32 Slot, FString& CycleInfo, FString& HPLV, FString& AttackLV);
#pragma endregion

#pragma region Delegate & Call Funck
	UPROPERTY(BlueprintAssignable)
	FOnFinshedSvaeGameDelegate OnFinshedSvaeGame;

	UFUNCTION()
	void OnSaveGameCompleted(const FString& SlotName, int32 SlotNum, bool bSuccess);
#pragma endregion

private:
#pragma region SaveDatas
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

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FArtifactData EquipedArtifactData;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<int32, FArtifactData>SavedArtifactInventory;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FModuleSaveData>SavedEquipedModule;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<EBookType, FInventoryMagicModule>SavedModuleInventory;
#pragma endregion

	UMageAndSeekerSaveGame* CreateNewSaveData(int32 Slot);
	void OverrideGameData(UMageAndSeekerSaveGame* SaveGameInstance);
	void OverridePlayerStatus(UMageAndSeekerSaveGame* SaveGameInstance);
	void OverrideBookData(UMageAndSeekerSaveGame* SaveGameInstance);
	void OverrideArtifactData(UMageAndSeekerSaveGame* SaveGameInstance);
	void OverrideModuleData(UMageAndSeekerSaveGame* SaveGameInstance);
	void ExecuteAsyncSave(int32 Slot, UMageAndSeekerSaveGame* SaveGameInstance);
};
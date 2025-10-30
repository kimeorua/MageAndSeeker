// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Props/Artifact/BaseArtifact.h"
#include "Type/MageAndSeekerStruct.h"
#include "EquipmentSubsystem.generated.h"

class UMagicModule;

UCLASS(Abstract, Blueprintable)
class MAGEANDSEEKER_API UEquipmentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
#pragma region Basic
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
#pragma endregion

#pragma region ArtifactFunc
	UFUNCTION(BlueprintCallable)
	UBaseArtifact* CreateArtifact();

	UBaseArtifact* CreateArtifact(int32 ID, FArtifactData Data);

	UFUNCTION(BlueprintCallable)
	void LoadAndCreateArtifact(int32 ID, FArtifactData Data);

	UFUNCTION(BlueprintCallable)
	UBaseArtifact* ChangeArtifact(int32 ChangeArtifactID, UBaseArtifact* OldArtifact);

	using FArtifactInventoryMap = TMap<int32, UBaseArtifact*>;
	GETTER(FArtifactInventoryMap, ArtifactInventory);
#pragma endregion

#pragma region Module
	void CreateModule(EBookType Type, FEquippedMagicModule& ModuleData, APawn* Pawn);
	void AddModuleToInventory(EBookType Type, FEquippedMagicModule ModuleData);
	FInventoryMagicModule GetModuleInInventory(EBookType Type);
#pragma endregion

private:
	UPROPERTY()
	TMap<int32, UBaseArtifact*>ArtifactInventory;

	UPROPERTY()
	TMap<EBookType, FInventoryMagicModule>ModuleInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Artifacte", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<UBaseArtifact>>CreatableArtifacts;

	UPROPERTY(EditAnywhere, Category = "Module", meta = (AllowPrivateAccess = "true"))
	UDataTable* ModuleDataTable;
};

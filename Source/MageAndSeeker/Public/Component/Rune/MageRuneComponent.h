// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "Component/Rune/Interface/RuneManagementInterface.h"
#include "Interface/SaveLoadInterface.h"
#include "Type/Structs/SaveDataStructs.h"
#include "Type/Structs/GamePlayStructs.h"
#include "MageRuneComponent.generated.h"

class UMagicRune;

UCLASS()
class MAGEANDSEEKER_API UMageRuneComponent : public UPawnExtensionComponent, public IRuneManagementInterface, public ISaveLoadInterface
{
	GENERATED_BODY()

public:
	UMageRuneComponent();

	virtual void RegisterRunes(EElementalType ElementalType, const TArray<FRuneCreateData>& InDatas) override;

	FEquipedRunes GetEquipedRuneDatas(EElementalType Type);

	FEquipedRunes GetInventoryRuneDatas(EElementalType Type);

	void SaveData_Implementation(UMageAndSeekerSaveGame* SaveGame) override;

	void LoadData_Implementation(const UMageAndSeekerSaveGame* SaveGame) override;

	void RuneApply(EElementalType Type, FProjectileSpec& Spec);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Runes")
	TMap<EElementalType, FEquipedRunes> EquipedRunes;

	UPROPERTY(VisibleAnywhere, Category = "Runes")
	TMap<EElementalType, FEquipedRunes> InventoryRunes;

	FSavedBookRuneData RuneCreateData_Equiped;

	FSavedBookRuneData RuneCreateData_Inventorty;

	void RuneComponentInit();

	void InventoryRuneCreate(EElementalType ElementalType, const TArray<FRuneCreateData>& InDatas);
};

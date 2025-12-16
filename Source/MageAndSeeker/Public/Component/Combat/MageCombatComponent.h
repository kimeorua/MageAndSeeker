// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/CombatComponent.h"
#include "Type/Structs/GamePlayStructs.h"
#include "Interface/SaveLoadInterface.h"
#include "MageCombatComponent.generated.h"

class AMagicBook;
class AWeaponBase;

UCLASS()
class MAGEANDSEEKER_API UMageCombatComponent : public UCombatComponent, public ISaveLoadInterface
{
	GENERATED_BODY()
	
public:
	UMageCombatComponent();

	virtual void RegisterWeapons_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void BookChange(EElementalType Type);

	FBookData GetBookDataFromType(EElementalType Type) const;

	void SaveData_Implementation(UMageAndSeekerSaveGame* SaveGame) override;

	void LoadData_Implementation(const UMageAndSeekerSaveGame* SaveGame) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon | MagicBook")
	AMagicBook* MagicBook;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | MagicBook", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMagicBook> MagicBookClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | MagicBook", meta = (AllowPrivateAccess = "true"))
	FName MagicBookSocket;

	UPROPERTY(VisibleAnywhere, Category = "Weapon | Staff")
	AWeaponBase* Staff;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Staff", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <AWeaponBase> StaffClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Staff", meta = (AllowPrivateAccess = "true"))
	FName StaffSocket;

	UPROPERTY(VisibleAnywhere, Category = "Book Data", meta = (AllowPrivateAccess = "true"))
	TMap<EElementalType, FBookData>MagicBookDatas;

	UPROPERTY(VisibleAnywhere, Category = "Book Data", meta = (AllowPrivateAccess = "true"))
	FBookData CurrentBookData;

	void BookInit();
};
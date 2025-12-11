// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "Component/Rune/Interface/RuneManagementInterface.h"
#include "MageRuneComponent.generated.h"

class UMagicRune;

UCLASS()
class MAGEANDSEEKER_API UMageRuneComponent : public UPawnExtensionComponent, public IRuneManagementInterface
{
	GENERATED_BODY()

public:
	UMageRuneComponent();

	virtual void RegisterRunes(EElementalType ElementalType, const TArray<FRuneCreateData>& InDatas) override;

	FEquipedRunes GetEquipedRuneDatas(EElementalType Type);

	FEquipedRunes GetInventoryRuneDatas(EElementalType Type);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Runes")
	TMap<EElementalType, FEquipedRunes> EquipedRunes;

	UPROPERTY(VisibleAnywhere, Category = "Runes")
	TMap<EElementalType, FEquipedRunes> InventoryRunes;

	void RuneComponentInit();
};

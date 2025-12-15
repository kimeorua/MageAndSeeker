// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "Interface/SaveLoadInterface.h"
#include "MageStatSaveComponent.generated.h"

class UAbilitySystemComponent;

UCLASS()
class MAGEANDSEEKER_API UMageStatSaveComponent : public UPawnExtensionComponent, public ISaveLoadInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

protected:
	virtual void BeginPlay() override;

public:
	void SaveData_Implementation(UMageAndSeekerSaveGame* SaveGame) override;
	void LoadData_Implementation(const UMageAndSeekerSaveGame* SaveGame) override;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterHUD.h"
#include "Type/Enums/GamePlayEnums.h"
#include "MageHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMageHUD : public UCharacterHUD
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAPChange(float Persent);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCombatMode(bool bIsComabat);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCurrentMana(float Persent);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMaxMana(float Count);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBookIcon(EElementalType Type);
};

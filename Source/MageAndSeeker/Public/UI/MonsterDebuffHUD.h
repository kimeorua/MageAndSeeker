// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterHUD.h"
#include "MonsterDebuffHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMonsterDebuffHUD : public UCharacterHUD
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFrozenIcon();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCurseIcon();
};

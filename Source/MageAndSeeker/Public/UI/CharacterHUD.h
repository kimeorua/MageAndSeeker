// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UCharacterHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHPBar(float Persent);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMaxHPBar(float LV);
};

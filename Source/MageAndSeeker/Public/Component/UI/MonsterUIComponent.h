// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/UIComponent.h"
#include "UI/CharacterHUD.h"
#include "MonsterUIComponent.generated.h"

class UCharacterHUD;
class UMonsterDebuffHUD;

UCLASS()
class MAGEANDSEEKER_API UMonsterUIComponent : public UUIComponent
{
	GENERATED_BODY()

public:
	void BindWidget(UCharacterHUD* UI);

	UFUNCTION(BlueprintCallable)
	void OnDebuffUpdate(FGameplayTag EffectTag);

private:
	UMonsterDebuffHUD* DebuffHUD;
};

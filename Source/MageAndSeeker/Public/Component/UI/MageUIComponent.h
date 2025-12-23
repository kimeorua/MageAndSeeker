// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/UIComponent.h"
#include "Type/Enums/GamePlayEnums.h"
#include "MageUIComponent.generated.h"

class UMageHUD;

UCLASS()
class MAGEANDSEEKER_API UMageUIComponent : public UUIComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnChangedUIShow(bool bIsShow);

	UFUNCTION(BlueprintCallable)
	void OnChangedCombatMode(bool bIsComabat);

	UFUNCTION(BlueprintCallable)
	void OnChangedBookIcon(EElementalType Type);

	virtual void InitCharacterUI(ABaseCharacter* Owenr) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnMaxHPChanged(const FOnAttributeChangeData& Data) override;

private:
	void OnCurrentAPChanged(const FOnAttributeChangeData& Data);

	void OnCurrentManaChanged(const FOnAttributeChangeData& Data);

	void OnMaxManaChanged(const FOnAttributeChangeData& Data);
};

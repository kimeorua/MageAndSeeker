// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/Enums/GamePlayEnums.h"
#include "DungeonMakerUI.generated.h"

class UDungeonOption;
class UButton;

UCLASS()
class MAGEANDSEEKER_API UDungeonMakerUI : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(meta = (BindWidget))
	UDungeonOption* DugeonElemental;

	UPROPERTY(meta = (BindWidget))
	UDungeonOption* DugeonDropItem;

	UPROPERTY(meta = (BindWidget))
	UDungeonOption* DugeonMonsterLevel;

	UPROPERTY(meta = (BindWidget))
	UButton* DungeonOpenButton;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InteractionEnd();

protected:
	virtual void NativeConstruct() override;

private:
	EDungeonElemental SelectedElemental;

	EDungeonDropItem SelectedDropItem;

	EDungeonMonsterLevel SelectedMonsterLevel;

	UFUNCTION()
	void OnOpenButton();

	UFUNCTION()
	void OnDungeonOptionChanged(EDungeonOptionType Type, int32 Index);
};
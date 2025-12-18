// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/Enums/GamePlayEnums.h"
#include "DungeonOption.generated.h"

class UButton;
class UWidgetSwitcher;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDungeonOptionChange, EDungeonOptionType, Option, int32, SelectedIndex);

UCLASS()
class MAGEANDSEEKER_API UDungeonOption : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* PreButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PostButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* IconChanger;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DropText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDungeonOptionType OptionType;

	FDungeonOptionChange OnOptionChanged;

	UFUNCTION()
	void PreButtonClicked();

	UFUNCTION()
	void PostButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> TooltipArr;

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

private:
	int32 IndexNum = 0;
};

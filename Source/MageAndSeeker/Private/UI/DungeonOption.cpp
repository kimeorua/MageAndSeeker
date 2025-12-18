// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DungeonOption.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UDungeonOption::PreButtonClicked()
{
	if (IndexNum <= 0) { IndexNum = IconChanger->GetNumWidgets() - 1; }
	else	{ --IndexNum;	}

	IconChanger->SetActiveWidgetIndex(IndexNum);
	DropText->SetText(FText::FromString(TooltipArr[IndexNum]));

	OnOptionChanged.Broadcast(OptionType, IndexNum);
}

void UDungeonOption::PostButtonClicked()
{
	if (IndexNum >= IconChanger->GetNumWidgets() - 1)	{ IndexNum = 0; }
	else { ++IndexNum; }

	IconChanger->SetActiveWidgetIndex(IndexNum);
	DropText->SetText(FText::FromString(TooltipArr[IndexNum]));

	OnOptionChanged.Broadcast(OptionType, IndexNum);
}

void UDungeonOption::NativeConstruct()
{
	Super::NativeConstruct();

	PreButton->OnClicked.AddDynamic(this, &UDungeonOption::PreButtonClicked);
	PostButton->OnClicked.AddDynamic(this, &UDungeonOption::PostButtonClicked);
}

void UDungeonOption::NativePreConstruct()
{
	Super::NativePreConstruct();

	IndexNum = 0;
	IconChanger->SetActiveWidgetIndex(IndexNum);

	if (TooltipArr.Num() <= 0) { return; }

	DropText->SetText(FText::FromString(TooltipArr[IndexNum]));

	OnOptionChanged.Broadcast(OptionType, IndexNum);
}

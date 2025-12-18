// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DungeonMakerUI.h"
#include "Components/Button.h"
#include "UI/DungeonOption.h"

#include "DebugHelper.h"

void UDungeonMakerUI::NativeConstruct()
{
	Super::NativeConstruct();

	DungeonOpenButton->OnClicked.AddDynamic(this, &UDungeonMakerUI::OnOpenButton);

	DugeonElemental->OptionType = EDungeonOptionType::Elemental;
	DugeonDropItem->OptionType = EDungeonOptionType::DropItem;
	DugeonMonsterLevel->OptionType = EDungeonOptionType::MonsterLevel;

	DugeonElemental->OnOptionChanged.AddDynamic(this, &UDungeonMakerUI::OnDungeonOptionChanged);
	DugeonDropItem->OnOptionChanged.AddDynamic(this, &UDungeonMakerUI::OnDungeonOptionChanged);
	DugeonMonsterLevel->OnOptionChanged.AddDynamic(this, &UDungeonMakerUI::OnDungeonOptionChanged);
}

void UDungeonMakerUI::OnOpenButton()
{
	InteractionEnd();

	const UEnum* EnumPtr_Elemntal = StaticEnum<EDungeonElemental>();
	FString Str1 = EnumPtr_Elemntal->GetDisplayNameTextByValue((int64)SelectedElemental).ToString();

	const UEnum* EnumPtr_Drop = StaticEnum<EDungeonDropItem>();
	FString Str2 = EnumPtr_Drop->GetDisplayNameTextByValue((int64)SelectedDropItem).ToString();

	const UEnum* EnumPtr_Level = StaticEnum<EDungeonMonsterLevel>();
	FString Str3 = EnumPtr_Level->GetDisplayNameTextByValue((int64)SelectedMonsterLevel).ToString();

	DebugHelper::Print(Str1);
	DebugHelper::Print(Str2);
	DebugHelper::Print(Str3);
}

void UDungeonMakerUI::OnDungeonOptionChanged(EDungeonOptionType Type, int32 Index)
{
	switch (Type)
	{
	case EDungeonOptionType::Elemental:
		SelectedElemental = static_cast<EDungeonElemental>(Index);
		break;
	case EDungeonOptionType::DropItem:
		SelectedDropItem = static_cast<EDungeonDropItem>(Index);
		break;
	case EDungeonOptionType::MonsterLevel:
		SelectedMonsterLevel = static_cast<EDungeonMonsterLevel>(Index);
		break;
	default:
		break;
	}
}

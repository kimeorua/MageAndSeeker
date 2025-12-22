// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DungeonMakerUI.h"
#include "Components/Button.h"
#include "UI/DungeonOption.h"
#include "Subsystem/DungeonMakerSubsystem.h"

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

	UDungeonMakerSubsystem* DungeonMakerSubsystem = GetGameInstance()->GetSubsystem<UDungeonMakerSubsystem>();

	if (!DungeonMakerSubsystem) { return; }

	DungeonMakerSubsystem->MoveToDungeon();

	DungeonMakerSubsystem->SpawnMonster(SelectedElemental, SelectedDropItem, SelectedMonsterLevel);
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

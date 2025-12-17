// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Rune/MageRuneComponent.h"

#include "Props/Rune/MagicRune.h"

#include "SaveGame/MageAndSeekerSaveGame.h"

#include "DebugHelper.h"

UMageRuneComponent::UMageRuneComponent()
{
}

void UMageRuneComponent::RegisterRunes(EElementalType ElementalType, const TArray<FRuneCreateData>& InDatas)
{
	EquipedRunes[ElementalType].EquipedRunes.Empty();

	switch (ElementalType)
	{
	case EElementalType::None:
		break;
	case EElementalType::Fire:
		RuneCreateData_Equiped.FireRuneData.Empty();
		break;
	case EElementalType::Ice:
		RuneCreateData_Equiped.IceRuneData.Empty();
		break;
	case EElementalType::Lightning:
		RuneCreateData_Equiped.LightningRuneData.Empty();
		break;
	case EElementalType::MAX:
		break;
	default:
		break;
	}

	for (FRuneCreateData Data : InDatas)
	{
		if (!IsValid(Data.CreateRuneClass)) { continue; }

		bool FindSame = false;

		UMagicRune* NewRune = NewObject<UMagicRune>(GetWorld(), Data.CreateRuneClass);
		FRuneData RuneData;
		RuneData.RuneID = Data.RuneID;
		RuneData.RuneLevel = Data.RuneLevel;
		RuneData.RuneApplyType = Data.RuneApplyType;
		NewRune->RuneInit(RuneData);

		EquipedRunes[ElementalType].EquipedRunes.Add(NewRune);

		switch (ElementalType)
		{
		case EElementalType::None:
			break;
		case EElementalType::Fire:
			RuneCreateData_Equiped.FireRuneData.Add(Data);
			break;
		case EElementalType::Ice:
			RuneCreateData_Equiped.IceRuneData.Add(Data);
			break;
		case EElementalType::Lightning:
			RuneCreateData_Equiped.LightningRuneData.Add(Data);
			break;
		case EElementalType::MAX:
			break;
		default:
			break;
		}

		for (UMagicRune* InventoryRune : InventoryRunes[ElementalType].EquipedRunes)
		{
			if (InventoryRune->GetRuneData().RuneID == Data.RuneID)
			{
				InventoryRune->RuneInit(RuneData);
				FindSame = true;
				break;
			}
		}
		if (!FindSame) 
		{
			InventoryRunes[ElementalType].EquipedRunes.Add(NewRune); 

			switch (ElementalType)
			{
			case EElementalType::None:
				break;
			case EElementalType::Fire:
				RuneCreateData_Inventorty.FireRuneData.Add(Data);
				break;
			case EElementalType::Ice:
				RuneCreateData_Inventorty.IceRuneData.Add(Data);
				break;
			case EElementalType::Lightning:
				RuneCreateData_Inventorty.LightningRuneData.Add(Data);
				break;
			case EElementalType::MAX:
				break;
			default:
				break;
			}
		}
	}
}

FEquipedRunes UMageRuneComponent::GetEquipedRuneDatas(EElementalType Type)
{
	if (EquipedRunes.Contains(Type))
	{
		return EquipedRunes[Type];
	}
	else
	{
		return FEquipedRunes();
	}
}

FEquipedRunes UMageRuneComponent::GetInventoryRuneDatas(EElementalType Type)
{
	if (InventoryRunes.Contains(Type))
	{
		return InventoryRunes[Type];
	}
	else
	{
		return FEquipedRunes();
	}
}

void UMageRuneComponent::SaveData_Implementation(UMageAndSeekerSaveGame* SaveGame)
{
	SaveGame->SavedEquipedRuneData.FireRuneData = RuneCreateData_Equiped.FireRuneData;
	SaveGame->SavedEquipedRuneData.IceRuneData = RuneCreateData_Equiped.IceRuneData;
	SaveGame->SavedEquipedRuneData.LightningRuneData = RuneCreateData_Equiped.LightningRuneData;

	SaveGame->SavedInventoryRuneData.FireRuneData = RuneCreateData_Inventorty.FireRuneData;
	SaveGame->SavedInventoryRuneData.IceRuneData = RuneCreateData_Inventorty.IceRuneData;
	SaveGame->SavedInventoryRuneData.LightningRuneData = RuneCreateData_Inventorty.LightningRuneData;
}

void UMageRuneComponent::LoadData_Implementation(const UMageAndSeekerSaveGame* SaveGame)
{
	InventoryRuneCreate(EElementalType::Fire, SaveGame->SavedInventoryRuneData.FireRuneData);
	InventoryRuneCreate(EElementalType::Ice, SaveGame->SavedInventoryRuneData.IceRuneData);
	InventoryRuneCreate(EElementalType::Lightning, SaveGame->SavedInventoryRuneData.LightningRuneData);

	if (!SaveGame->SavedEquipedRuneData.FireRuneData.IsEmpty())
	{
		RegisterRunes(EElementalType::Fire, SaveGame->SavedEquipedRuneData.FireRuneData);
	}
	else
	{
		EquipedRunes[EElementalType::Fire].EquipedRunes.Empty();
	}

	if (!SaveGame->SavedEquipedRuneData.IceRuneData.IsEmpty())
	{
		RegisterRunes(EElementalType::Ice, SaveGame->SavedEquipedRuneData.IceRuneData);
	}
	else
	{
		EquipedRunes[EElementalType::Ice].EquipedRunes.Empty();
	}

	if (!SaveGame->SavedEquipedRuneData.LightningRuneData.IsEmpty())
	{
		RegisterRunes(EElementalType::Lightning, SaveGame->SavedEquipedRuneData.LightningRuneData);
	}
	else
	{
		EquipedRunes[EElementalType::Lightning].EquipedRunes.Empty();
	}
}

void UMageRuneComponent::BeginPlay()
{
	Super::BeginPlay();
	RuneComponentInit();
}

void UMageRuneComponent::RuneComponentInit()
{
	for (uint8 i = (uint8)EElementalType::None + 1; i < (uint8)EElementalType::MAX; ++i)
	{
		EElementalType Type = static_cast<EElementalType>(i);
		FEquipedRunes Temp;
		Temp.Type = Type;
		Temp.EquipedRunes.Empty();

		EquipedRunes.FindOrAdd(Type, Temp);
		InventoryRunes.FindOrAdd(Type, Temp);
	}
}

void UMageRuneComponent::InventoryRuneCreate(EElementalType ElementalType, const TArray<FRuneCreateData>& InDatas)
{
	for (FRuneCreateData Data : InDatas)
	{
		if (!IsValid(Data.CreateRuneClass)) { continue; }

		UMagicRune* NewRune = NewObject<UMagicRune>(GetWorld(), Data.CreateRuneClass);
		FRuneData RuneData;
		RuneData.RuneID = Data.RuneID;
		RuneData.RuneLevel = Data.RuneLevel;
		RuneData.RuneApplyType = Data.RuneApplyType;
		NewRune->RuneInit(RuneData);

		InventoryRunes[ElementalType].EquipedRunes.Add(NewRune);

		switch (ElementalType)
		{
		case EElementalType::None:
			break;
		case EElementalType::Fire:
			RuneCreateData_Inventorty.FireRuneData.Add(Data);
			break;
		case EElementalType::Ice:
			RuneCreateData_Inventorty.IceRuneData.Add(Data);
			break;
		case EElementalType::Lightning:
			RuneCreateData_Inventorty.LightningRuneData.Add(Data);
			break;
		case EElementalType::MAX:
			break;
		default:
			break;
		}
	}
}
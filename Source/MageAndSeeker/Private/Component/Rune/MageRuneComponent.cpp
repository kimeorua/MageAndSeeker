// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Rune/MageRuneComponent.h"

#include "Props/Rune/MagicRune.h"

#include "DebugHelper.h"

UMageRuneComponent::UMageRuneComponent()
{
}

void UMageRuneComponent::RegisterRunes(EElementalType ElementalType, const TArray<FRuneCreateData>& InDatas)
{
	EquipedRunes[ElementalType].EquipedRunes.Empty();

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

		for (UMagicRune* InventoryRune : InventoryRunes[ElementalType].EquipedRunes)
		{
			if (InventoryRune->GetRuneData().RuneID == Data.RuneID)
			{
				InventoryRune->RuneInit(RuneData);
				FindSame = true;
				break;
			}
		}
		if (!FindSame) { InventoryRunes[ElementalType].EquipedRunes.Add(NewRune); }
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/EquipmentSubsystem.h"
#include "Type/MageAndSeekerStruct.h"
#include "Props/Module/MagicModule.h"
#include "Character/MageCharacter.h"
#include "Component/Weapon/MageWeaponComponent.h"
#include "Interface/WeaponInterface.h"

#include "DebugHelper.h"

#pragma region Basic
void UEquipmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("UEquipmentSubsystem Init");
}

void UEquipmentSubsystem::Deinitialize()
{
}
#pragma endregion

#pragma region Artifact
UBaseArtifact* UEquipmentSubsystem::CreateArtifact()
{
	UBaseArtifact* NewArtifact = nullptr;

	if (CreatableArtifacts.Num() == 0)
	{
		return nullptr;
	}

	TArray<int32> Keys;
	CreatableArtifacts.GetKeys(Keys);

	int32 RandomKeyIndex = FMath::RandRange(0, Keys.Num() - 1);
	int32 SelectedKey = Keys[RandomKeyIndex];

	TSubclassOf<UBaseArtifact> ArtifactClass = CreatableArtifacts.FindRef(SelectedKey);

	if (ArtifactClass)
	{
		NewArtifact = NewObject<UBaseArtifact>(this, ArtifactClass);
		CreatableArtifacts.Remove(SelectedKey);
		ArtifactInventory.Add(NewArtifact->GetArtifactID(), NewArtifact);
	}

	return NewArtifact;
}

UBaseArtifact* UEquipmentSubsystem::CreateArtifact(int32 ID, FArtifactData Data)
{
	UBaseArtifact* NewArtifact = nullptr;

	if (ID < 0) { return nullptr; }

	TSubclassOf<UBaseArtifact> ArtifactClass = CreatableArtifacts.FindRef(ID);

	if (ArtifactClass)
	{
		NewArtifact = NewObject<UBaseArtifact>(this, ArtifactClass);
		NewArtifact->SetArtifactID(Data.ArtifactID);
		NewArtifact->SetArtifactName(Data.ArtifactName);
		NewArtifact->SetUpgradeLevel(Data.UpgradeLevel);
	}

	return NewArtifact;
}

void UEquipmentSubsystem::LoadAndCreateArtifact(int32 ID, FArtifactData Data)
{
	ArtifactInventory.Empty();

	TSubclassOf<UBaseArtifact> ArtifactClass = CreatableArtifacts.FindRef(ID);

	if (ArtifactClass)
	{
		UBaseArtifact* NewArtifact = NewObject<UBaseArtifact>(this, ArtifactClass);
		CreatableArtifacts.Remove(ID);

		NewArtifact->SetArtifactID(Data.ArtifactID);
		NewArtifact->SetArtifactName(Data.ArtifactName);
		NewArtifact->SetUpgradeLevel(Data.UpgradeLevel);

		ArtifactInventory.Add(NewArtifact->GetArtifactID(), NewArtifact);
	}
}

UBaseArtifact* UEquipmentSubsystem::ChangeArtifact(int32 ChangeArtifactID, UBaseArtifact* OldArtifact)
{
	if (ArtifactInventory.Contains(ChangeArtifactID))
	{
		ArtifactInventory.Add(OldArtifact->GetArtifactID(), OldArtifact);

		return ArtifactInventory[ChangeArtifactID];
	}
	return nullptr;
}
#pragma endregion

#pragma region Module
void UEquipmentSubsystem::CreateModule(EBookType Type, FEquippedMagicModule& ModuleData, APawn* Pawn)
{
	FName ID = ModuleData.ModuleID;
	int32 LV = ModuleData.ModuleLevel;

	static const FString ContextString(TEXT("Item Data Context"));
	FMagicModuleDataTableRow* Row = ModuleDataTable->FindRow<FMagicModuleDataTableRow>(ID, ContextString);
	if (Row)
	{
		UMagicModule* NewModule = NewObject<UMagicModule>(this, Row->MagicModuleClass);
		NewModule->Initialize(Row->ModuleID, Row->ApplyPhase, LV);

		if (!ModuleInventory.Contains(Type))
		{
			ModuleInventory.Add(Type, FMagicModuleMap());
		}

		ModuleInventory[Type].Modules.Add(NewModule->GetModuleID(), NewModule);

		if (IsValid(Pawn))
		{
			AMageCharacter* Mage = Cast<AMageCharacter>(Pawn);
			UMageWeaponComponent* MageWeaponComponent = Cast<IWeaponInterface>(Mage)->GetMageWeaponComponent();

			MageWeaponComponent->RegisterModule(Type, NewModule);
		}
	}
}
#pragma endregion

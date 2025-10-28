#include "Subsystem/SaveLoadSubsystem.h"
#include "SaveGame/MageAndSeekerSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MageCharacter.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "GAS/AttributeSet/MageAttributeSet.h"
#include "Component/Weapon/MageWeaponComponent.h"
#include "Subsystem/EquipmentSubsystem.h"

#include "DebugHelper.h"

#pragma region Basic
void USaveLoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("USaveLoadSubsystem Init");
}

void USaveLoadSubsystem::Deinitialize()
{
	OnFinshedSvaeGame.Clear();
}
#pragma endregion

#pragma region Save & Load

UMageAndSeekerSaveGame* USaveLoadSubsystem::CreateNewSaveData(int32 Slot)
{
	UMageAndSeekerSaveGame* SaveGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::CreateSaveGameObject(UMageAndSeekerSaveGame::StaticClass()));
	if (IsValid(SaveGameInstance))
	{
		SaveGameInstance->CurrentCycle = 1;
		SaveGameInstance->HPLevel = 0.0f;
		SaveGameInstance->AttackLevel = 0.0f;
		CurrentSlot = Slot;

		for (EBookType Type : {EBookType::Fire, EBookType::Ice, EBookType::Lightning})
		{
			FBookData Book;
			Book.BookLevel = 1;
			Book.BookType = Type;
			SaveGameInstance->BookDatas.FindOrAdd(Type, Book);
		}
		SaveGameInstance->EquipedArtifactData = FArtifactData();
		SaveGameInstance->SavedArtifactInventory.Empty();
	}
	return SaveGameInstance;
}
void USaveLoadSubsystem::OverrideGameData(UMageAndSeekerSaveGame* SaveGameInstance)
{
	OverridePlayerStatus(SaveGameInstance);
	OverrideBookData(SaveGameInstance);
	OverrideArtifactData(SaveGameInstance);
}

void USaveLoadSubsystem::OverridePlayerStatus(UMageAndSeekerSaveGame* SaveGameInstance)
{
	AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Mage) { return; }

	const UMageAttributeSet* MageAttributSet = Mage->GetAbilitySystemComponent()->GetSet<UMageAttributeSet>();
	//SaveGameInstance->CurrentCycle = this->CurrentCycle;
	//SaveGameInstance->HPLevel = MageAttributSet->GetHPLevel();
	//SaveGameInstance->HPLevel = MageAttributSet->GetAttackLevel();

	//--------------테스트용--------------//
	this->CurrentCycle++;
	SaveGameInstance->CurrentCycle = this->CurrentCycle;
	SaveGameInstance->HPLevel = MageAttributSet->GetHPLevel() + 1.0f;
	SaveGameInstance->AttackLevel = MageAttributSet->GetAttackLevel() + 1.0f;
	//--------------테스트용--------------//
}

void USaveLoadSubsystem::OverrideBookData(UMageAndSeekerSaveGame* SaveGameInstance)
{
	AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Mage) { return; }

	UMageWeaponComponent* MageWeaponComponent = Cast<IWeaponInterface>(Mage)->GetMageWeaponComponent();
	if (!MageWeaponComponent) { return; }

	for (EBookType Type : {EBookType::Fire, EBookType::Ice, EBookType::Lightning})
	{
		//--------------테스트용--------------//
		FBookData Data = MageWeaponComponent->GetBookData(Type);
		if (Data.BookType == EBookType::Fire)
		{
			Data.BookLevel = 4;
		}
		//--------------테스트용--------------//
		SaveGameInstance->BookDatas.FindOrAdd(Type) = Data;
	}
}

void USaveLoadSubsystem::OverrideArtifactData(UMageAndSeekerSaveGame* SaveGameInstance)
{
	AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Mage) { return; }

	UMageWeaponComponent* MageWeaponComponent = Cast<IWeaponInterface>(Mage)->GetMageWeaponComponent();
	if (!MageWeaponComponent) { return; }

	if (MageWeaponComponent && MageWeaponComponent->GetArtifact())
	{
		SaveGameInstance->EquipedArtifactData.ArtifactID = MageWeaponComponent->GetArtifact()->GetArtifactID();
		SaveGameInstance->EquipedArtifactData.ArtifactName = MageWeaponComponent->GetArtifact()->GetArtifactName();
		SaveGameInstance->EquipedArtifactData.UpgradeLevel = MageWeaponComponent->GetArtifact()->GetUpgradeLevel();
	}

	if (UEquipmentSubsystem* EquipmentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEquipmentSubsystem>())
	{
		SaveGameInstance->SavedArtifactInventory.Empty();

		for (auto& Pair : EquipmentSubsystem->GetArtifactInventory())
		{
			if (!IsValid(Pair.Value)) { continue; }

			FArtifactData Data;
			Data.ArtifactID = Pair.Value->GetArtifactID();
			Data.ArtifactName = Pair.Value->GetArtifactName();
			Data.UpgradeLevel = Pair.Value->GetUpgradeLevel();

			SaveGameInstance->SavedArtifactInventory.Add(Pair.Key, Data);
		}
	}
}

void USaveLoadSubsystem::ExecuteAsyncSave(int32 Slot, UMageAndSeekerSaveGame* SaveGameInstance)
{
	if (!IsValid(SaveGameInstance)) { return; }

	FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);

	FAsyncSaveGameToSlotDelegate SaveFinishedDelegate;
	SaveFinishedDelegate.BindUObject(this, &ThisClass::OnSaveGameCompleted);

	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotName, 0, SaveFinishedDelegate);
}

void USaveLoadSubsystem::SaveGame(int32 Slot, bool bIsNewGame)
{
	UMageAndSeekerSaveGame* SaveGameInstance = nullptr;

	if (bIsNewGame)
	{
		SaveGameInstance = CreateNewSaveData(Slot);
	}
	else
	{
		SaveGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::CreateSaveGameObject(UMageAndSeekerSaveGame::StaticClass()));
		OverrideGameData(SaveGameInstance);
	}
	ExecuteAsyncSave(Slot, SaveGameInstance);
}

void USaveLoadSubsystem::LoadGame(int32 Slot)
{
	FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UMageAndSeekerSaveGame* LoadGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (LoadGameInstance)
		{
			CurrentCycle = LoadGameInstance->CurrentCycle;
			CurrentSlot = Slot;
			HPLevel = LoadGameInstance->HPLevel;
			AttackLevel = LoadGameInstance->AttackLevel;
			BookDatas = LoadGameInstance->BookDatas;

			EquipedArtifactData = LoadGameInstance->EquipedArtifactData;
			SavedArtifactInventory.Empty();

			for (auto& Pair : LoadGameInstance->SavedArtifactInventory)
			{
				SavedArtifactInventory.Add(Pair.Key, Pair.Value);
			}
		}
	}
}

FBookData USaveLoadSubsystem::GetLoadedBookData(EBookType BookType)
{
	FBookData ReturnData;

	FString SlotName = TEXT("SaveSlot") + FString::FromInt(CurrentSlot);
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UMageAndSeekerSaveGame* LoadGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (LoadGameInstance)
		{
			if (LoadGameInstance->BookDatas.Contains(BookType))
			{
				ReturnData = LoadGameInstance->BookDatas.FindRef(BookType);
			}
		}
	}
	return ReturnData;
}
#pragma endregion

#pragma region GetFunc
bool USaveLoadSubsystem::GetSaveInfo(int32 Slot, FString& CycleInfo, FString& HPLV, FString& AttackLV)
{
	FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UMageAndSeekerSaveGame* LoadGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (LoadGameInstance)
		{
			CycleInfo = FString::FromInt(LoadGameInstance->CurrentCycle);
			HPLV = FString::FromInt(FMath::FloorToInt32(LoadGameInstance->HPLevel));
			AttackLV = FString::FromInt(FMath::FloorToInt32(LoadGameInstance->AttackLevel));
			return true;
		}
	}
	return false;
}
#pragma endregion

#pragma region Delegage Call Func
void USaveLoadSubsystem::OnSaveGameCompleted(const FString& SlotName, int32 SlotNum, bool bSuccess)
{
	if (bSuccess)
	{
		OnFinshedSvaeGame.Broadcast();
	}
}
#pragma endregion
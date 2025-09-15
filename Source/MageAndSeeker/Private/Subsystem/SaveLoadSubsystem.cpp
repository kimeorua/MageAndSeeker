#include "Subsystem/SaveLoadSubsystem.h"
#include "SaveGame/MageAndSeekerSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MageCharacter.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "GAS/AttributeSet/MageAttributeSet.h"
#include "Component/Weapon/MageWeaponComponent.h"

#include "DebugHelper.h"

void USaveLoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("USaveLoadSubsystem Init");
}

void USaveLoadSubsystem::Deinitialize()
{
}

void USaveLoadSubsystem::SaveGame(int32 Slot, bool bIsNewGame)
{
	UMageAndSeekerSaveGame* SaveGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::CreateSaveGameObject(UMageAndSeekerSaveGame::StaticClass()));
	if (IsValid(SaveGameInstance))
	{
		if (bIsNewGame) 
		{
			SaveGameInstance->CurrentCycle = 1;
			SaveGameInstance->HPLevel = 0.0f;
			SaveGameInstance->AttackLevel = 0.0f;
			CurrentSlot = Slot;

			FBookData FireBook, IceBook, LightningBook;
			FireBook.BookLevel = 3;
			FireBook.BookType = EBookType::Fire;
			SaveGameInstance->BookDatas.Add(EBookType::Fire, FireBook);

			IceBook.BookLevel = 2;
			IceBook.BookType = EBookType::Ice;
			SaveGameInstance->BookDatas.Add(EBookType::Ice, IceBook);

			LightningBook.BookLevel = 1;
			LightningBook.BookType = EBookType::Lightning;
			SaveGameInstance->BookDatas.Add(EBookType::Lightning, LightningBook);
		}
		else
		{	
			UWorld* World = GetGameInstance()->GetWorld();
			AMageCharacter* Mage = Cast<AMageCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			const UMageAttributeSet* MageAttributSet = Mage->GetAbilitySystemComponent()->GetSet<UMageAttributeSet>();
			UMageWeaponComponent* MageWeaponComponent = Cast<IWeaponInterface>(Mage)->GetMageWeaponComponent();

			//SaveGameInstance->CurrentCycle = this->CurrentCycle;
			//SaveGameInstance->HPLevel = MageAttributSet->GetHPLevel();
			//SaveGameInstance->HPLevel = MageAttributSet->GetAttackLevel();
			FBookData FireBook = MageWeaponComponent->GetBookData(EBookType::Fire);
			FBookData IceBook = MageWeaponComponent->GetBookData(EBookType::Ice);
			FBookData LightningBook = MageWeaponComponent->GetBookData(EBookType::Lightning);

			SaveGameInstance->BookDatas.Add(EBookType::Fire, FireBook);
			SaveGameInstance->BookDatas.Add(EBookType::Ice, IceBook);
			SaveGameInstance->BookDatas.Add(EBookType::Lightning, LightningBook);

			// 테스트용
			CurrentCycle++;
			SaveGameInstance->CurrentCycle = this->CurrentCycle;
			SaveGameInstance->HPLevel = MageAttributSet->GetHPLevel() + 1.0f;
			SaveGameInstance->AttackLevel = MageAttributSet->GetAttackLevel() + 1.0f;

			FireBook = MageWeaponComponent->GetBookData(EBookType::Fire);
			FireBook.BookLevel = 4;
			SaveGameInstance->BookDatas.Add(EBookType::Fire, FireBook);
		}
		FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);

		FAsyncSaveGameToSlotDelegate SaveFinishedDelegate;
		SaveFinishedDelegate.BindUObject(this, &ThisClass::OnSaveGameCompleted);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotName, 0, SaveFinishedDelegate);
	}
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
		}
	}
}

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

void USaveLoadSubsystem::OnSaveGameCompleted(const FString& SlotName, int32 SlotNum, bool bSuccess)
{
	if (bSuccess)
	{
		OnFinshedSvaeGame.Broadcast();
	}
}

FBookData USaveLoadSubsystem::GetLoadedBookData(EBookType BookType)
{
	FBookData ReturnData;

	if (BookDatas.Contains(BookType))
	{
		ReturnData = BookDatas.FindRef(BookType);
	}
	return ReturnData;
}

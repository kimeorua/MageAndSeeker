#include "Subsystem/SaveLoadSubsystem.h"
#include "SaveGame/MageAndSeekerSaveGame.h"
#include "Kismet/GameplayStatics.h"
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
		}
		else
		{	
			// 테스트용
			SaveGameInstance->CurrentCycle = ++this->CurrentCycle;
			//SaveGameInstance->CurrentCycle = this->CurrentCycle;
		}
		FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
	}
}

void USaveLoadSubsystem::LoadGame(int32 Slot)
{
	FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UMageAndSeekerSaveGame* LoadGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot01"), 0));

		if (LoadGameInstance)
		{
			CurrentCycle = LoadGameInstance->CurrentCycle;

			CurrentSlot = Slot;
		}
	}
}

bool USaveLoadSubsystem::GetSaveInfo(int32 Slot, FString& CycleInfo)
{
    FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UMageAndSeekerSaveGame* LoadGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (LoadGameInstance)
		{
			CycleInfo = FString::FromInt(LoadGameInstance->CurrentCycle);
			return true;
		}
	}
	return false;
}

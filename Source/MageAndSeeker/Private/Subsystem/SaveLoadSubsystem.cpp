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
			CurrentSlot = Slot;
		}
		else
		{	
			// 테스트용
			CurrentCycle++;
			SaveGameInstance->CurrentCycle = CurrentCycle;
			//SaveGameInstance->CurrentCycle = this->CurrentCycle;
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

void USaveLoadSubsystem::OnSaveGameCompleted(const FString& SlotName, int32 SlotNum, bool bSuccess)
{
	if (bSuccess)
	{
		OnFinshedSvaeGame.Broadcast();
	}
}
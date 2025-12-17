#include "Subsystem/SaveLoadSubsystem.h"
#include "SaveGame/MageAndSeekerSaveGame.h"

#include "Kismet/GameplayStatics.h"

#include "Character/MageCharacter.h"

#include "GAS/MASAbilitySystemComponent.h"
#include "Interface/SaveLoadInterface.h"
#include "GAS/AttributeSet/MageAttributeSet.h"

#include "DebugHelper.h"

void USaveLoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("USaveLoadSubsystem Init");
}

void USaveLoadSubsystem::Deinitialize()
{
}

void USaveLoadSubsystem::SaveGameAsync(const int32 SlotNum, bool bIsNewGame, AActor* TargetActor)
{
    if (!IsValid(TargetActor)) { return; }

    CurrentSaveGame = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::CreateSaveGameObject(UMageAndSeekerSaveGame::StaticClass()));

    if (!CurrentSaveGame) { return; }

    if (bIsNewGame)
    {
        MakeNewGame();
    }
    else
    {
        CollectSaveData(TargetActor, CurrentSaveGame);
    }

    SlotIndex = SlotNum;

    FString SlotName = TEXT("SaveSlot") + FString::FromInt(SlotNum);

    UGameplayStatics::AsyncSaveGameToSlot
    (
        CurrentSaveGame, 
        SlotName, 
        0, 
        FAsyncSaveGameToSlotDelegate::CreateUObject(this, &USaveLoadSubsystem::OnSaveCompleted)
    );
}

void USaveLoadSubsystem::LoadGameAsync(const int32 SlotNum, AActor* TargetActor)
{
    if (!IsValid(TargetActor)) { return; }

    FString SlotName = TEXT("SaveSlot") + FString::FromInt(SlotNum);

    UGameplayStatics::AsyncLoadGameFromSlot
    (
        SlotName,
        0,
        FAsyncLoadGameFromSlotDelegate::CreateLambda
        (
            [this, TargetActor](const FString&, int32, USaveGame* LoadedGame)
            {
                UMageAndSeekerSaveGame* SaveGame = Cast<UMageAndSeekerSaveGame>(LoadedGame);
                if (!SaveGame || !IsValid(TargetActor)) { return; }
                ApplyLoadData(TargetActor, SaveGame);
            }
        )
    );
}

bool USaveLoadSubsystem::GetMageStatFromSlot(int32 SaveSlot, int32& OutHPLevel, int32& OutAttackLevel)
{
    FString SlotName = TEXT("SaveSlot") + FString::FromInt(SaveSlot);

    if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0)) { return false; }

    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
    UMageAndSeekerSaveGame* SaveGame = Cast<UMageAndSeekerSaveGame>(LoadedGame);

    if (!SaveGame) { return false; }

    OutHPLevel = SaveGame->MageStat.HPLevel;
    OutAttackLevel = SaveGame->MageStat.AttackLevel;

    return true;
}

FStatSaveData USaveLoadSubsystem::CurrentSaveDataFromStat() const
{
    FString SlotName = TEXT("SaveSlot") + FString::FromInt(SlotIndex);

    if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0)) {return FStatSaveData(); }

    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
    UMageAndSeekerSaveGame* SaveGame = Cast<UMageAndSeekerSaveGame>(LoadedGame);

    if (!SaveGame) { return FStatSaveData(); }

    return SaveGame->MageStat;
}

void USaveLoadSubsystem::OnSaveCompleted(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
    DebugHelper::Print("Save End");
}

void USaveLoadSubsystem::CollectSaveData(AActor* TargetActor, UMageAndSeekerSaveGame* SaveGame)
{
    TArray<UActorComponent*> Components;
    TargetActor->GetComponents(Components);

    for (UActorComponent* Comp : Components)
    {
        if (Comp->Implements<USaveLoadInterface>())
        {
            ISaveLoadInterface::Execute_SaveData(Comp, SaveGame);
        }
    }
}

void USaveLoadSubsystem::ApplyLoadData(AActor* TargetActor, UMageAndSeekerSaveGame* SaveGame)
{
    TArray<UActorComponent*> Components;
    TargetActor->GetComponents(Components);

    for (UActorComponent* Comp : Components)
    {
        if (Comp->Implements<USaveLoadInterface>())
        {
            ISaveLoadInterface::Execute_LoadData(Comp, SaveGame);
        }
    }
}

void USaveLoadSubsystem::MakeNewGame()
{
    CurrentSaveGame->MageStat.HPLevel = 0;
    CurrentSaveGame->MageStat.AttackLevel = 0;

    CurrentSaveGame->BookLevelData.FireBookLevel = 1;
    CurrentSaveGame->BookLevelData.IceBookLevel = 1;
    CurrentSaveGame->BookLevelData.LightningBookLevel = 1;

    CurrentSaveGame->SavedEquipedRuneData.AllEmpty();
    CurrentSaveGame->SavedInventoryRuneData.AllEmpty();
}
#include "Subsystem/SaveLoadSubsystem.h"
#include "SaveGame/MageAndSeekerSaveGame.h"

#include "Kismet/GameplayStatics.h"

#include "Character/MageCharacter.h"

#include "GAS/MASAbilitySystemComponent.h"

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

void USaveLoadSubsystem::SaveGameAsync(const int32 SlotNum, bool bIsNewGame)
{
    CurrentSaveGame = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::CreateSaveGameObject(UMageAndSeekerSaveGame::StaticClass()));

    CurrentSlotIndex = SlotNum;
    FString SlotName = TEXT("SaveSlot") + FString::FromInt(SlotNum);

    CollectStatData(bIsNewGame);

    UGameplayStatics::AsyncSaveGameToSlot
    (
        CurrentSaveGame, 
        SlotName, 
        0, 
        FAsyncSaveGameToSlotDelegate::CreateUObject(this, &USaveLoadSubsystem::OnSaveCompleted)
    );
}

void USaveLoadSubsystem::LoadGameAsync(const int32 SlotNum)
{
    CurrentSlotIndex = SlotNum;
    FString SlotName = TEXT("SaveSlot") + FString::FromInt(SlotNum);

    UGameplayStatics::AsyncLoadGameFromSlot
    (
        SlotName,
        0,
        FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &USaveLoadSubsystem::OnLoadCompleted)
    );
}

bool USaveLoadSubsystem::GetMageStat(int32 Slot, int32& HPLevel, int32& AttackLevel)
{
    FString SlotName = TEXT("SaveSlot") + FString::FromInt(Slot);
    if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
    {
        UMageAndSeekerSaveGame* LoadGameInstance = Cast<UMageAndSeekerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

        if (LoadGameInstance)
        {
            HPLevel = LoadGameInstance->MageStat.HPLevel;
            AttackLevel = LoadGameInstance->MageStat.AttackLevel;
            return true;
        }
    }
    return false;
}

void USaveLoadSubsystem::CollectStatData(bool IsNew)
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    APawn* Pawn = PC->GetPawn();

    if (IsNew)
    {
        CurrentSaveGame->MageStat.AttackLevel = 0;
        CurrentSaveGame->MageStat.HPLevel = 0;
    }
    else
    {
        UAbilitySystemComponent* ASC = Pawn->FindComponentByClass<UAbilitySystemComponent>();

        if (!ASC) return;

        const UMageAttributeSet* MageAttributeSet = ASC->GetSet<UMageAttributeSet>();

        if (!MageAttributeSet) { return; }

       // CurrentSaveGame->MageStat.AttackLevel = MageAttributeSet->GetAttackLevel();
       // CurrentSaveGame->MageStat.HPLevel = MageAttributeSet->GetHPLevel();

        // Test
        CurrentSaveGame->MageStat.AttackLevel = MageAttributeSet->GetAttackLevel() + 1;
        CurrentSaveGame->MageStat.HPLevel = MageAttributeSet->GetHPLevel() + 1;
        // Test
    }
}

void USaveLoadSubsystem::OnSaveCompleted(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
    DebugHelper::Print("Save End");
}

void USaveLoadSubsystem::OnLoadCompleted(const FString& SlotName, int32 UserIndex, USaveGame* LoadedGame)
{
    DebugHelper::Print("Load End");

    UMageAndSeekerSaveGame* LoadedSaveGame = Cast<UMageAndSeekerSaveGame>(LoadedGame);

    CurrentSaveGame->MageStat.HPLevel = LoadedSaveGame->MageStat.HPLevel;
    CurrentSaveGame->MageStat.AttackLevel = LoadedSaveGame->MageStat.AttackLevel;
}
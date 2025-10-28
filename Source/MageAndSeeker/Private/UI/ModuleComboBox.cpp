// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ModuleComboBox.h"
#include "Types/SlateEnums.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Subsystem/EquipmentSubsystem.h"
#include "Character/MageCharacter.h"
#include "Component/Weapon/MageWeaponComponent.h"
#include "Interface/WeaponInterface.h"

#include "DebugHelper.h"

void UModuleComboBox::NativeConstruct()
{
    Super::NativeConstruct();

    if (const AMageCharacter* Mage = Cast<AMageCharacter>(GetOwningPlayerPawn()))
    {
        if (const UMageWeaponComponent* MageWeaponComponent = Cast<IWeaponInterface>(Mage)->GetMageWeaponComponent())
        {
            EquippedModules = MageWeaponComponent->GetEquippedModules(Type);
        }
    }

    RebuildBlockedModules();
    UpdateAllComboBoxes();

    ComboBox_Slot1->OnSelectionChanged.AddDynamic(this, &ThisClass::OnModuleSelected_Slot1);
    ComboBox_Slot2->OnSelectionChanged.AddDynamic(this, &ThisClass::OnModuleSelected_Slot2);
    ComboBox_Slot3->OnSelectionChanged.AddDynamic(this, &ThisClass::OnModuleSelected_Slot3);
    ComboBox_Slot4->OnSelectionChanged.AddDynamic(this, &ThisClass::OnModuleSelected_Slot4);
    ApplyButton->OnClicked.AddDynamic(this, &ThisClass::Call_CreateModules);
}

void UModuleComboBox::OnModuleSelected_Slot1(FString SelectedOption, ESelectInfo::Type SelectionType)
{
    if (SelectionType != ESelectInfo::Direct)
    {
        OnModuleSelected(ComboBox_Slot1, 0, SelectedOption);
    }
}

void UModuleComboBox::OnModuleSelected_Slot2(FString SelectedOption, ESelectInfo::Type SelectionType)
{
    if (SelectionType != ESelectInfo::Direct)
    {
        OnModuleSelected(ComboBox_Slot2, 1, SelectedOption);
    }
}

void UModuleComboBox::OnModuleSelected_Slot3(FString SelectedOption, ESelectInfo::Type SelectionType)
{
    if (SelectionType != ESelectInfo::Direct)
    {
        OnModuleSelected(ComboBox_Slot3, 2, SelectedOption);
    }
}

void UModuleComboBox::OnModuleSelected_Slot4(FString SelectedOption, ESelectInfo::Type SelectionType)
{
    if (SelectionType != ESelectInfo::Direct)
    {
        OnModuleSelected(ComboBox_Slot4, 3, SelectedOption);
    }
}

void UModuleComboBox::Call_CreateModules()
{
    if (AMageCharacter* Mage = Cast<AMageCharacter>(GetOwningPlayerPawn()))
    {
        UMageWeaponComponent* MageWeaponComponent = Cast<IWeaponInterface>(Mage)->GetMageWeaponComponent();

        MageWeaponComponent->ResetModules(Type);
    }

    if (UEquipmentSubsystem* EquipmentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEquipmentSubsystem>())
    {
        for (FEquippedMagicModule Module : EquippedModules)
        {
            EquipmentSubsystem->CreateModule(Type, Module, GetOwningPlayerPawn());
        }
    }
}

void UModuleComboBox::UpdateAllComboBoxes()
{
    UpdateComboBox(ComboBox_Slot1, 0);
    UpdateComboBox(ComboBox_Slot2, 1);
    UpdateComboBox(ComboBox_Slot3, 2);
    UpdateComboBox(ComboBox_Slot4, 3);
}

void UModuleComboBox::UpdateComboBox(UComboBoxString* ComboBox, int32 SlotIndex)
{
    if (!ComboBox || !MagicModuleDataTable) { return; }

    ComboBox->ClearOptions();

    FString EmptyOption = TEXT("Select Module");
    ComboBox->AddOption(EmptyOption);

    static const FString Context(TEXT("MagicModule"));
    TArray<FMagicModuleDataTableRow*> AllRows;
    MagicModuleDataTable->GetAllRows(Context, AllRows);

    FString CurrentlyEquippedDisplayName = EmptyOption;
    FName CurrentModuleID = NAME_None;
    int32 CurrentModuleLevel = 0;

    if (EquippedModules.IsValidIndex(SlotIndex))
    {
        CurrentModuleID = EquippedModules[SlotIndex].ModuleID;
        CurrentModuleLevel = EquippedModules[SlotIndex].ModuleLevel;
    }

    if (CurrentModuleID != NAME_None)
    {
        if (const FMagicModuleDataTableRow* Row = MagicModuleDataTable->FindRow<FMagicModuleDataTableRow>(CurrentModuleID, Context))
        {
            CurrentlyEquippedDisplayName = FString::Printf(TEXT("%s (Lv.%d)"), *Row->ModuleName.ToString(), CurrentModuleLevel);
            ComboBox->AddOption(CurrentlyEquippedDisplayName);
        }
    }

    for (const auto* Row : AllRows)
    {
        if (!Row) { continue; }
        const FName& ModuleID = Row->ModuleID;

        if (ModuleID == CurrentModuleID) { continue; }
        bool bIsEquippedInOtherSlot = false;

        for (int32 i = 0; i < EquippedModules.Num(); ++i)
        {
            if (i != SlotIndex && EquippedModules[i].ModuleID == ModuleID && EquippedModules[i].ModuleID != NAME_None)
            {
                bIsEquippedInOtherSlot = true;
                break;
            }
        }

        if (bIsEquippedInOtherSlot || BlockedModules.Contains(ModuleID)) { continue;  }

        FString DisplayText = FString::Printf(TEXT("%s (Lv.%d)"), *Row->ModuleName.ToString(), 1);
        ComboBox->AddOption(DisplayText);
    }
    ComboBox->RefreshOptions();
    ComboBox->SetSelectedOption(CurrentlyEquippedDisplayName);
}

void UModuleComboBox::RebuildBlockedModules()
{
    if (!MagicModuleDataTable) return;

    BlockedModules.Empty();

    static const FString Context(TEXT("MagicModule"));

    for (const FEquippedMagicModule& Equipped : EquippedModules)
    {
        if (Equipped.ModuleID == NAME_None) continue;

        if (const FMagicModuleDataTableRow* Row = MagicModuleDataTable->FindRow<FMagicModuleDataTableRow>(Equipped.ModuleID, Context))
        {
            TArray<FString> ParsedIDs;
            Row->LimitModulesID.ParseIntoArray(ParsedIDs, TEXT(","), true);
            for (const FString& ID : ParsedIDs)
            {
                BlockedModules.Add(FName(*ID));
            }
        }
    }
}

void UModuleComboBox::OnModuleSelected(UComboBoxString* ComboBox, int32 SlotIndex, FString SelectedOption)
{
    if (!MagicModuleDataTable) { return; }

    static const FString Context(TEXT("MagicModule"));
    TArray<FMagicModuleDataTableRow*> AllRows;
    MagicModuleDataTable->GetAllRows(Context, AllRows);

    for (const auto* Row : AllRows)
    {
        if (Row && SelectedOption.StartsWith(Row->ModuleName.ToString()))
        {
            if (EquippedModules.Num() <= SlotIndex)
            {
                EquippedModules.SetNum(SlotIndex + 1);
            }
            EquippedModules[SlotIndex].ModuleID = Row->ModuleID;
            EquippedModules[SlotIndex].ModuleLevel = 1;

            break;
        }
    }
    RebuildBlockedModules();
    UpdateAllComboBoxes();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/MageAndSeekerStruct.h"
#include "ModuleComboBox.generated.h"

class UComboBoxString;
class UButton;

UCLASS()
class MAGEANDSEEKER_API UModuleComboBox : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ComboBox_Slot1;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ComboBox_Slot2;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ComboBox_Slot3;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ComboBox_Slot4;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UDataTable* MagicModuleDataTable;

    UPROPERTY(meta = (BindWidget))
    UButton* ApplyButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EBookType Type = EBookType::Fire;

    UFUNCTION()
    void OnModuleSelected_Slot1(FString SelectedOption, ESelectInfo::Type SelectionType);
    UFUNCTION()
    void OnModuleSelected_Slot2(FString SelectedOption, ESelectInfo::Type SelectionType);
    UFUNCTION()
    void OnModuleSelected_Slot3(FString SelectedOption, ESelectInfo::Type SelectionType);
    UFUNCTION()
    void OnModuleSelected_Slot4(FString SelectedOption, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void Call_CreateModules();

    UPROPERTY()
    TArray<FEquippedMagicModule> EquippedModules;

    UPROPERTY()
    TSet<FName> BlockedModules;

    void UpdateAllComboBoxes();
    void UpdateComboBox(UComboBoxString* ComboBox, int32 SlotIndex);
    void OnModuleSelected(UComboBoxString* ComboBox, int32 SlotIndex, FString SelectedOption);
    void RebuildBlockedModules();
};

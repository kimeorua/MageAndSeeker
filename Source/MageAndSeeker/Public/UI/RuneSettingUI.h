// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/Enums/GamePlayEnums.h"
#include "RuneSettingUI.generated.h"

class UScrollBox;
class URuneSlot;
class UButton;
class UWidgetSwitcher;
class UImage;

USTRUCT(BlueprintType)
struct FCreatedRuneData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName RuneID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 RuneLevel;
};

UCLASS()
class MAGEANDSEEKER_API URuneSettingUI : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UScrollBox* RuneScroll;

    UPROPERTY(meta = (BindWidget))
    UButton* RuneSlot_1;

    UPROPERTY(meta = (BindWidget))
    UButton* RuneSlot_2;

    UPROPERTY(meta = (BindWidget))
    UButton* RuneSlot_3;

    UPROPERTY(meta = (BindWidget))
    UButton* RuneSlot_4;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* UI_Changer;

    UPROPERTY(meta = (BindWidget))
    UImage* RuneIcone_Slot1;

    UPROPERTY(meta = (BindWidget))
    UImage* RuneIcone_Slot2;

    UPROPERTY(meta = (BindWidget))
    UImage* RuneIcone_Slot3;

    UPROPERTY(meta = (BindWidget))
    UImage* RuneIcone_Slot4;

    UPROPERTY(meta = (BindWidget))
    UButton* UndoButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ApplyButton;

    UPROPERTY(meta = (BindWidget))
    UUserWidget* MassageWidget;

    /*UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetElementalType(const EElementalType Type) { Elemental = Type; }*/

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "UI|Data")
    class UDataTable* RuneDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Data")
    TSubclassOf<URuneSlot> RuneSlotWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Data", meta = (AllowPrivateAccess = "true"))
    EElementalType Elemental;

    UPROPERTY()
    TArray<UButton*>RuneSlots;

    UPROPERTY()
    TArray<URuneSlot*> RuneArray;

    UPROPERTY()
    TMap<int32, EMagicRuneType>ApplyedRuneTypes;

    TMap<int32, FCreatedRuneData>CrateableRunes;

    int32 CurrentSlotNum;

    UFUNCTION()
    void SettingSlotIcon(UTexture2D* RuneIcon, EMagicRuneType RuneType);

    UFUNCTION()
    FORCEINLINE void OnClick_Slot1() { SettingSlot(1); }

    UFUNCTION()
    FORCEINLINE void OnClick_Slot2() { SettingSlot(2); }

    UFUNCTION()
    FORCEINLINE void OnClick_Slot3() { SettingSlot(3); }

    UFUNCTION()
    FORCEINLINE void OnClick_Slot4() { SettingSlot(4); }

    void SettingSlot(int32 SlotNum);

    void EnabiledRune();

    void SettingRuneIcon(int32 SlotNum, UTexture2D* Icon);

    UFUNCTION()
    void OnUndoButtonClicked();

    UFUNCTION()
    void RuneApply();

    UFUNCTION()
    void SetCreatedRunes(FName ID, int32 LV);

    void RuneSelectedSlotInit();
    void RuneSlotInit();
    void WidgetDataInit();

    void EquipedRunesSetting();
};

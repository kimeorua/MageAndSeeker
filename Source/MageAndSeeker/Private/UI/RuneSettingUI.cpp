// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RuneSettingUI.h"
#include "Kismet/GameplayStatics.h"

#include "UI/RuneSlot.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"

#include "Type/Structs/DataTableStructs.h"
#include "MageAndSeekerFunctionLibrary.h"

#include "Component/Combat/Interface/CombatInterface.h"
#include "Component/Combat/MageCombatComponent.h"
#include "Component/Rune/Interface/RuneManagementInterface.h"
#include "Component/Rune/MageRuneComponent.h"
#include "Props/Rune/MagicRune.h"


#include "DebugHelper.h"

const int32 MAX_BOOK_LEVEL = 4;

void URuneSettingUI::NativeConstruct()
{
	Super::NativeConstruct();

    RuneSlotInit();
    RuneSelectedSlotInit();
    WidgetDataInit();

    UndoButton->OnClicked.AddDynamic(this, &URuneSettingUI::OnUndoButtonClicked);
    ApplyButton->OnClicked.AddDynamic(this, &URuneSettingUI::RuneApply);
}

void URuneSettingUI::SettingSlotIcon(UTexture2D* RuneIcon, EMagicRuneType RuneType)
{
    UI_Changer->SetActiveWidgetIndex(0);
    ApplyedRuneTypes.Add(CurrentSlotNum, RuneType);

    EnabiledRune();
    SettingRuneIcon(CurrentSlotNum, RuneIcon);
}

void URuneSettingUI::SettingSlot(int32 SlotNum)
{
    UI_Changer->SetActiveWidgetIndex(1);
    CurrentSlotNum = SlotNum;
}

void URuneSettingUI::EnabiledRune()
{
    for (URuneSlot* RuneSlot : RuneArray)
    {
        RuneSlot->SetIsEnabled(true);
    }

    for (URuneSlot* RuneSlot : RuneArray)
    {
        for (const TPair<int32, EMagicRuneType>& Pair : ApplyedRuneTypes)
        {
            if (RuneSlot->RuneType == Pair.Value)
            {
                RuneSlot->SetIsEnabled(false);
            }
        }
    }
}

void URuneSettingUI::SettingRuneIcon(int32 SlotNum, UTexture2D* Icon)
{
    switch (SlotNum)
    {
    case 1:
        RuneIcone_Slot1->SetBrushFromTexture(Icon);
        RuneIcone_Slot1->SetOpacity(1.0f);
        break;
    case 2:
        RuneIcone_Slot2->SetBrushFromTexture(Icon);
        RuneIcone_Slot2->SetOpacity(1.0f);
        break;
    case 3:
        RuneIcone_Slot3->SetBrushFromTexture(Icon);
        RuneIcone_Slot3->SetOpacity(1.0f);
        break;
    case 4:
        RuneIcone_Slot4->SetBrushFromTexture(Icon);
        RuneIcone_Slot4->SetOpacity(1.0f);
        break;
    default:
        break;
    }
}

void URuneSettingUI::OnUndoButtonClicked()
{
    switch (CurrentSlotNum)
    {
    case 1:
        RuneIcone_Slot1->SetBrushFromTexture(nullptr);
        RuneIcone_Slot1->SetOpacity(0.0f);
        break;
    case 2:
        RuneIcone_Slot2->SetBrushFromTexture(nullptr);
        RuneIcone_Slot2->SetOpacity(0.0f);
        break;
    case 3:
        RuneIcone_Slot3->SetBrushFromTexture(nullptr);
        RuneIcone_Slot3->SetOpacity(0.0f);
        break;
    case 4:
        RuneIcone_Slot4->SetBrushFromTexture(nullptr);
        RuneIcone_Slot4->SetOpacity(0.0f);
        break;
    default:
        break;
    }
    UI_Changer->SetActiveWidgetIndex(0);
    ApplyedRuneTypes.Add(CurrentSlotNum, EMagicRuneType::None);

    FCreatedRuneData TempData;
    TempData.RuneID = "";
    TempData.RuneLevel = 1;

    CrateableRunes.Add(CurrentSlotNum, TempData);

    EnabiledRune();
}

void URuneSettingUI::RuneApply()
{
    static const FString Context(TEXT("MagicRune_Create"));

    AActor* TargetActor = GetOwningPlayerPawn();

    TScriptInterface<IInterface> FoundInterface = UMageAndSeekerFunctionLibrary::FindComponentByInterface(TargetActor, URuneManagementInterface::StaticClass());
    TScriptInterface<IRuneManagementInterface> RuneHandler = FoundInterface.GetObject();

    TArray<FRuneCreateData>MakeRuneDatas;

    for (int32 i = 1; i < 5; i++)
    {
        FName ID = CrateableRunes[i].RuneID;

        if (ID == "None") { continue; }

        FMagicRuneDataTable* FoundRow = RuneDataTable->FindRow<FMagicRuneDataTable>(ID, Context);
        if (FoundRow)
        {
            FRuneCreateData NewRuneData;
            NewRuneData.RuneID = FoundRow->RuneID;
            NewRuneData.RuneLevel = CrateableRunes[i].RuneLevel;
            NewRuneData.RuneApplyType = FoundRow->RuneApplyType;
            NewRuneData.CreateRuneClass = FoundRow->MagicRune_BP;

            MakeRuneDatas.AddUnique(NewRuneData);
        }
    }
    RuneHandler->RegisterRunes(Elemental, MakeRuneDatas);

    MassageWidget->SetVisibility(ESlateVisibility::Visible);
}

void URuneSettingUI::SetCreatedRunes(FName ID, int32 LV)
{
    FCreatedRuneData TempData;
    TempData.RuneID = ID;
    TempData.RuneLevel = LV;
    CrateableRunes.Add(CurrentSlotNum, TempData);
}

void URuneSettingUI::RuneSelectedSlotInit()
{
    RuneSlots = { RuneSlot_1 , RuneSlot_2 , RuneSlot_3 , RuneSlot_4 };

    AActor* TargetActor = GetOwningPlayerPawn();
    if (TargetActor)
    {
        UMageCombatComponent* MageCombatComponent = TargetActor->GetComponentByClass<UMageCombatComponent>();
        FBookData BookData = MageCombatComponent->GetBookDataFromType(Elemental);

        if (BookData.BookLevel < MAX_BOOK_LEVEL)
        {
            for (int i = BookData.BookLevel; i < RuneSlots.Num(); i++)
            {
                RuneSlots[i]->SetIsEnabled(false);
            }
        }
    }
    RuneSlot_1->OnClicked.AddDynamic(this, &URuneSettingUI::OnClick_Slot1);
    RuneSlot_2->OnClicked.AddDynamic(this, &URuneSettingUI::OnClick_Slot2);
    RuneSlot_3->OnClicked.AddDynamic(this, &URuneSettingUI::OnClick_Slot3);
    RuneSlot_4->OnClicked.AddDynamic(this, &URuneSettingUI::OnClick_Slot4);
}

void URuneSettingUI::RuneSlotInit()
{
    if (RuneDataTable)
    {
        static const FString Context(TEXT("MagicRune_RuneSelectSlot_Init"));
        TArray<FMagicRuneDataTable*> AllRows;
        RuneDataTable->GetAllRows(Context, AllRows);

        if (RuneScroll && RuneSlotWidgetClass)
        {
            RuneArray.Empty();

            for (FMagicRuneDataTable* Data : AllRows)
            {
                int32 LV = 1;

                URuneSlot* NewRuneSlot = CreateWidget<URuneSlot>(GetWorld(), RuneSlotWidgetClass);

                AActor* TargetActor = GetOwningPlayerPawn();
                UMageRuneComponent* MageRuneComponent = TargetActor->GetComponentByClass<UMageRuneComponent>();

                FEquipedRunes InvantoryData = MageRuneComponent->GetInventoryRuneDatas(Elemental);

                for (UMagicRune* InventoryRune : InvantoryData.EquipedRunes)
                {
                    if (InventoryRune->GetRuneData().RuneID == Data->RuneID)
                    {
                        LV = InventoryRune->GetRuneData().RuneLevel;
                    }
                }
                NewRuneSlot->SetRuneSlotText(Data->RuneName, LV);
                NewRuneSlot->SetIcon(Data->Icon);
                NewRuneSlot->SetRuneID(Data->RuneID);
                NewRuneSlot->SetRuneType(Data->RuneType);

                RuneScroll->AddChild(NewRuneSlot);

                NewRuneSlot->OnRuneSelected.AddDynamic(this, &URuneSettingUI::SettingSlotIcon);
                NewRuneSlot->SendRuneData.AddDynamic(this, &URuneSettingUI::SetCreatedRunes);
                RuneArray.AddUnique(NewRuneSlot);
            }
        }
    }
}

void URuneSettingUI::WidgetDataInit()
{
    ApplyedRuneTypes.Add(1, EMagicRuneType::None);
    ApplyedRuneTypes.Add(2, EMagicRuneType::None);
    ApplyedRuneTypes.Add(3, EMagicRuneType::None);
    ApplyedRuneTypes.Add(4, EMagicRuneType::None);

    FCreatedRuneData TempData;
    TempData.RuneID = "";
    TempData.RuneLevel = 1;

    CrateableRunes.Add(1, TempData);
    CrateableRunes.Add(2, TempData);
    CrateableRunes.Add(3, TempData);
    CrateableRunes.Add(4, TempData);

    EquipedRunesSetting();
}

void URuneSettingUI::EquipedRunesSetting()
{
    AActor* TargetActor = GetOwningPlayerPawn();
    UMageRuneComponent* MageRuneComponent = TargetActor->GetComponentByClass<UMageRuneComponent>();

    FEquipedRunes Data = MageRuneComponent->GetEquipedRuneDatas(Elemental);

    int32 Index = 1;

    if (Data.EquipedRunes.IsEmpty()) { return; }

    for (const UMagicRune* Rune : Data.EquipedRunes)
    {
        FRuneData RuneData = Rune->GetRuneData();

        static const FString Context(TEXT("EquipedRunesSetting"));
        FMagicRuneDataTable* FoundRow = RuneDataTable->FindRow<FMagicRuneDataTable>(RuneData.RuneID, Context);
        if (FoundRow)
        {
            SettingRuneIcon(Index, FoundRow->Icon);
            ApplyedRuneTypes.Add(Index, FoundRow->RuneType);

            FCreatedRuneData CreatedRuneData;
            CreatedRuneData.RuneID = FoundRow->RuneID;
            CreatedRuneData.RuneLevel = RuneData.RuneLevel;
            CrateableRunes.Add(Index, CreatedRuneData);
        }
        Index++;
    }
    EnabiledRune();
}

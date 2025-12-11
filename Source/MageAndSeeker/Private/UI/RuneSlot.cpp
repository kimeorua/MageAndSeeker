// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RuneSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "DebugHelper.h"

void URuneSlot::NativeConstruct()
{
    Super::NativeConstruct();

    RnueButton->OnClicked.AddDynamic(this, &URuneSlot::HandleClicked);
}

void URuneSlot::SetIcon(UTexture2D* NewTexture)
{
    if (RuneIcon)
    {
        RuneIcon->SetBrushFromTexture(NewTexture);
        RuneIcon->SetOpacity(1.0);

        IconTexture = NewTexture;
    }
}

void URuneSlot::SetRuneSlotText(FName RuneName, int32 RuneLevel)
{
    if (RuneNameText && RuneLevelText)
    {
        RuneNameText->SetText(FText::FromString(RuneName.ToString()));
        RuneLevelText->SetText(FText::AsNumber(RuneLevel));

        RuneLV = RuneLevel;
    }
}

void URuneSlot::HandleClicked()
{
    OnRuneSelected.Broadcast(IconTexture, RuneType);
    SendRuneData.Broadcast(RuneID, RuneLV);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/Enums/GamePlayEnums.h"
#include "RuneSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRuneSelected, UTexture2D*, RuneIcon, EMagicRuneType, RuneType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendRuneData, FName, RuneID, int32, RuneLV);

class UImage;
class UTextBlock;
class UButton;


UCLASS()
class MAGEANDSEEKER_API URuneSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	 virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* RuneIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* RuneBackgroundIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* RuneFrameIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RuneNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RuneLevelText;

	UPROPERTY(meta = (BindWidget))
	UButton* RnueButton;

	UPROPERTY()
	FOnRuneSelected OnRuneSelected;

	UPROPERTY()
	FSendRuneData SendRuneData;

	UPROPERTY()
	EMagicRuneType RuneType;

	UFUNCTION(BlueprintCallable)
	void SetIcon(UTexture2D* NewTexture);

	UFUNCTION(BlueprintCallable)
	void SetRuneSlotText(FName RuneName, int32 RuneLevel);

	UFUNCTION(BlueprintCallable)
	void SetRuneType(const EMagicRuneType Type) { RuneType = Type; }

	UFUNCTION(BlueprintCallable)
	void SetRuneID(const FName ID) { RuneID = ID; }

private:
	UPROPERTY()
	UTexture2D* IconTexture;

	FName RuneID;

	int32 RuneLV;

	UFUNCTION()
	void HandleClicked();
};

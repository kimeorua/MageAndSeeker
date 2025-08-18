// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MageAndSeekerWidget.generated.h"

class USaveLoadSubsystem;

UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On SaveLoad Subsystem Initalized"))
	void BP_OnSaveLoadSubsystemInitalized(USaveLoadSubsystem* SaveLoadSubsystem);
};

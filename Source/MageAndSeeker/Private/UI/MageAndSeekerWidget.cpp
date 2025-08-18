// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MageAndSeekerWidget.h"
#include "Subsystem/SaveLoadSubsystem.h"

void UMageAndSeekerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (USaveLoadSubsystem* SaveLoadSubsystem = GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		if (SaveLoadSubsystem)
		{
			BP_OnSaveLoadSubsystemInitalized(SaveLoadSubsystem);
		}
	}
}
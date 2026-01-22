// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MageHUD.h"
#include "Subsystem/DungeonMakerSubsystem.h"

#include "DebugHelper.h"

void UMageHUD::NativeConstruct()
{
	Super::NativeConstruct();

	UDungeonMakerSubsystem* DungeonMakerSubsystem = GetGameInstance()->GetSubsystem<UDungeonMakerSubsystem>();

	DungeonMakerSubsystem->OnCountdawnStart.AddDynamic(this, &UMageHUD::StartCountDawn);
}

void UMageHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bActivateCountdawn) { return; }

	Countdawn -= InDeltaTime;
	UpdateCountDawn(Countdawn);

	if (Countdawn <= 0.0f)
	{
		bActivateCountdawn = false;
		FinishCountdown();
	}
}

void UMageHUD::StartCountDawn()
{
	bActivateCountdawn = true;
	Countdawn = TotalCount;
}

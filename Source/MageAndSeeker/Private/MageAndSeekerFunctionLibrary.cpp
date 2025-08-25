// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAndSeekerFunctionLibrary.h"

void UMageAndSeekerFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EMASInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		if (World)
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}
	if (!PlayerController) { return; }

	FInputModeGameOnly GameOnlyMode;
	GameOnlyMode.SetConsumeCaptureMouseDown(false);

	FInputModeUIOnly UIOnly;

	switch (InInputMode)
	{
	case EMASInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->SetShowMouseCursor(false);
		break;
	case EMASInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnly);
		PlayerController->FlushPressedKeys();
		PlayerController->SetShowMouseCursor(true);
		break;
	default:
		break;
	}
}

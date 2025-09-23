// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAndSeekerFunctionLibrary.h"
#include "Subsystem/SaveLoadSubsystem.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

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
int32 UMageAndSeekerFunctionLibrary::GetCurrentCycle(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		USaveLoadSubsystem* SaveLoadSubsystem = World->GetGameInstance()->GetSubsystem<USaveLoadSubsystem>();

		return SaveLoadSubsystem->GetCurrentCycle();
	}
	else 
	{
		return 0;
	}
}

UMASAbilitySystemComponent* UMageAndSeekerFunctionLibrary::NativeGetMageASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UMASAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UMageAndSeekerFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UMASAbilitySystemComponent* ASC = NativeGetMageASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UMageAndSeekerFunctionLibrary::RemoveGameplayTagToActorIfFind(AActor* InActor, FGameplayTag TagToRemove)
{
	UMASAbilitySystemComponent* ASC = NativeGetMageASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

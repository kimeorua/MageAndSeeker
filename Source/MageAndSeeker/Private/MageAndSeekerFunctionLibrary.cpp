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

bool UMageAndSeekerFunctionLibrary::NativeDoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UMASAbilitySystemComponent* ASC = NativeGetMageASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UMageAndSeekerFunctionLibrary::BP_DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EMageAndSeekerConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoseActorHaveTag(InActor, TagToCheck) ? EMageAndSeekerConfirmType::Yes : EMageAndSeekerConfirmType::No;
}

UPARAM(DisplayName = "Found Interface")TScriptInterface<IInterface> UMageAndSeekerFunctionLibrary::FindComponentByInterface(AActor* TargetActor, TSubclassOf<UInterface> InterfaceClass)
{
	if (!TargetActor || !InterfaceClass) { return nullptr; }
	UObject* FoundObject = TargetActor->FindComponentByInterface(InterfaceClass);

	if (FoundObject) { return TScriptInterface<IInterface>(FoundObject); }

	return nullptr;
}
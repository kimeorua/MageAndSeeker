// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/MageUIComponent.h"
#include "UI/MageHUD.h"

#include "GAS/MASAbilitySystemComponent.h"
#include "GAS/AttributeSet/MageAttributeSet.h"
#include "GAS/AttributeSet/ArtifactAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

void UMageUIComponent::OnChangedUIShow(bool bIsShow)
{
	if (bIsShow)
	{
		HUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMageUIComponent::OnChangedCombatMode(bool bIsComabat)
{
	UMageHUD* MageHud = Cast<UMageHUD>(HUD);
	MageHud->UpdateCombatMode(bIsComabat);
}

void UMageUIComponent::OnChangedBookIcon(EElementalType Type)
{
	UMageHUD* MageHud = Cast<UMageHUD>(HUD);
	MageHud->UpdateBookIcon(Type);
}

void UMageUIComponent::BeginPlay()
{
	Super::BeginPlay();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
	if (!ASC) return;

	ASC->GetGameplayAttributeValueChangeDelegate(UArtifactAttributeSet::GetCurrentAPAttribute()).AddUObject(this, &UMageUIComponent::OnCurrentAPChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UMageAttributeSet::GetCurrentMPAttribute()).AddUObject(this, &UMageUIComponent::OnCurrentManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UMageAttributeSet::GetMaxMPAttribute()).AddUObject(this, &UMageUIComponent::OnMaxManaChanged);
}

void UMageUIComponent::OnCurrentAPChanged(const FOnAttributeChangeData& Data)
{
	UMageHUD* MageHud = Cast<UMageHUD>(HUD);

	if (MageHud)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
		const UArtifactAttributeSet* ArtifactAttributeSet = ASC->GetSet<UArtifactAttributeSet>();
		MageHud->UpdateAPChange(ArtifactAttributeSet->GetCurrentAP() / ArtifactAttributeSet->GetMaxAP());
	}
}

void UMageUIComponent::OnCurrentManaChanged(const FOnAttributeChangeData& Data)
{
	UMageHUD* MageHud = Cast<UMageHUD>(HUD);

	if (MageHud)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
		const UMageAttributeSet* MageAttributeSet = ASC->GetSet<UMageAttributeSet>();
		MageHud->UpdateCurrentMana(MageAttributeSet->GetCurrentMP() / MageAttributeSet->GetMaxMP());
	}
}

void UMageUIComponent::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
	UMageHUD* MageHud = Cast<UMageHUD>(HUD);

	if (MageHud)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
		const UMageAttributeSet* MageAttributeSet = ASC->GetSet<UMageAttributeSet>();
		MageHud->UpdateMaxMana(MageAttributeSet->GetMaxMP());
	}
}
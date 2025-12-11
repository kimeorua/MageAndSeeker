// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/UIComponent.h"

#include "GAS/MASAbilitySystemComponent.h"
#include "UI/CharacterHUD.h"
#include "Blueprint/UserWidget.h"

#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "GAS/AttributeSet/MageAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"

void UUIComponent::InitCharacterUI(ABaseCharacter* Owenr)
{
	if (CharacterHUDClass)
	{
		HUD = Cast<UCharacterHUD>(CreateWidget(Owenr->GetWorld(), CharacterHUDClass));
		HUD->AddToViewport();
	}
}

void UUIComponent::BeginPlay()
{
	Super::BeginPlay();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
	if (!ASC) return;

	ASC->GetGameplayAttributeValueChangeDelegate(UMASBaseAttributeSet::GetCurrentHPAttribute()).AddUObject(this, &UUIComponent::OnCurrentHPChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UMASBaseAttributeSet::GetMaxHPAttribute()).AddUObject(this, &UUIComponent::OnMaxHPChanged);
}

void UUIComponent::OnCurrentHPChanged(const FOnAttributeChangeData& Data)
{
	if (HUD)
	{
		UAbilitySystemComponent* ASC =UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
		const UMASBaseAttributeSet* MASBaseAttribute = ASC->GetSet<UMASBaseAttributeSet>();
		HUD->UpdateHPBar(MASBaseAttribute->GetCurrentHP() / MASBaseAttribute->GetMaxHP());
	}
}

void UUIComponent::OnMaxHPChanged(const FOnAttributeChangeData& Data)
{
	if (HUD)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
		const UMageAttributeSet* MageAttributeSet = ASC->GetSet<UMageAttributeSet>();
		HUD->UpdateMaxHPBar(MageAttributeSet->GetHPLevel());
	}
}
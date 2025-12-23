// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/UIComponent.h"

#include "GAS/MASAbilitySystemComponent.h"
#include "UI/CharacterHUD.h"
#include "Blueprint/UserWidget.h"

#include "GAS/AttributeSet/MASBaseAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "DebugHelper.h"

void UUIComponent::InitCharacterUI(ABaseCharacter* Owenr)
{
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
	
}
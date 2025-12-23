// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/MonsterUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"


void UMonsterUIComponent::BindWidget(UCharacterHUD* UI)
{
	if (!UI) { return; }
	HUD = UI;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
	if (!ASC) return;

	ASC->GetGameplayAttributeValueChangeDelegate(UMASBaseAttributeSet::GetCurrentHPAttribute()).AddUObject(this, &UMonsterUIComponent::OnCurrentHPChanged);
}
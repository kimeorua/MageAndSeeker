// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/MonsterUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "UI/MonsterDebuffHUD.h"
#include "MageAndSeekerGameplayTag.h"

#include "AbilitySystemBlueprintLibrary.h"


void UMonsterUIComponent::BindWidget(UCharacterHUD* UI)
{
	if (!UI) { return; }
	HUD = UI;

	DebuffHUD = Cast<UMonsterDebuffHUD>(UI);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningCharacter_Base());
	if (!ASC) return;

	ASC->GetGameplayAttributeValueChangeDelegate(UMASBaseAttributeSet::GetCurrentHPAttribute()).AddUObject(this, &UMonsterUIComponent::OnCurrentHPChanged);
}

void UMonsterUIComponent::OnDebuffUpdate(FGameplayTag EffectTag)
{
	if (EffectTag == MageAndSeekerGameplayTag::Monster_Status_Curse)
	{
		DebuffHUD->UpdateCurseIcon();
	}
	else if (EffectTag == MageAndSeekerGameplayTag::Monster_Status_FrozenCoolDawn)
	{
		DebuffHUD->UpdateFrozenIcon();
	}
}

void UMonsterUIComponent::UIHidden()
{
	if (!DebuffHUD) { return; }
	DebuffHUD->SetVisibility(ESlateVisibility::Hidden);
}

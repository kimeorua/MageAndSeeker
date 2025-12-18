// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatSave/MageStatSaveComponent.h"
#include "AbilitySystemComponent.h"
#include "SaveGame/MageAndSeekerSaveGame.h"
#include "GAS/AttributeSet/MageAttributeSet.h"

#include "DebugHelper.h"

void UMageStatSaveComponent::BeginPlay()
{
	Super::BeginPlay();
	ASC = GetOwningCharacter_Base()->GetAbilitySystemComponent();
}

void UMageStatSaveComponent::SaveData_Implementation(UMageAndSeekerSaveGame* SaveGame)
{
	if (SaveGame)
	{
		// TODO: Test 용으로 +1 함 정식 에선 +1 제거
		SaveGame->MageStat.HPLevel = ASC->GetNumericAttribute(UMageAttributeSet::GetHPLevelAttribute()) + 1;
		SaveGame->MageStat.AttackLevel = ASC->GetNumericAttribute(UMageAttributeSet::GetAttackLevelAttribute()) + 1;
	}
}

void UMageStatSaveComponent::LoadData_Implementation(const UMageAndSeekerSaveGame* SaveGame)
{
}
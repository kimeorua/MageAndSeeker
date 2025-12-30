// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/MageAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MageAndSeekerFunctionLibrary.h"
#include "MageAndSeekerGameplayTag.h"

#include "DebugHelper.h"

UMageAttributeSet::UMageAttributeSet()
{
	InitHPLevel(0.0f);
	InitAttackLevel(0.0f);
	InitCurrentMP(1.0f);
	InitMaxMP(1.0f);
	InitArmor(1.0f);
}

void UMageAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentMPAttribute())
	{
		float NewMP = FMath::Clamp(GetCurrentMP(), 0.0f, GetMaxMP());

		if (NewMP < GetMaxMP())
		{
			UMageAndSeekerFunctionLibrary::RemoveGameplayTagToActorIfFind(Data.Target.GetAvatarActor(), MageAndSeekerGameplayTag::Mage_Status_ManaFull);
		}
		else if (NewMP >= GetMaxMP())
		{
			UMageAndSeekerFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), MageAndSeekerGameplayTag::Mage_Status_ManaFull);
		}

		SetCurrentMP(NewMP);
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMPAttribute())
	{
		SetMaxMP(FMath::Max(GetMaxMP(), 0.0f));
	}
	else if (Data.EvaluatedData.Attribute == GetHPLevelAttribute())
	{
		float NewLevel = GetHPLevel() >= MaxLV ? MaxLV : GetHPLevel();
		SetHPLevel(NewLevel);
	}
	else if (Data.EvaluatedData.Attribute == GetAttackLevelAttribute())
	{
		float NewLevel = GetAttackLevel() >= MaxLV ? MaxLV : GetAttackLevel();
		SetAttackLevel(NewLevel);
	}
	else if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		float NewArmor = GetArmor() <= 0 ? 5 : GetArmor();
		SetArmor(NewArmor);
	}
}
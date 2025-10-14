// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/MageAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MageAndSeekerFunctionLibrary.h"
#include "Interface/PawnUIInterface.h"
#include "Component/UI/PawnUIComponent.h"
#include "Component/UI/MageUIComponent.h"

#include "DebugHelper.h"

UMageAttributeSet::UMageAttributeSet()
{
	InitHPLevel(0.0f);
	InitAttackLevel(0.0f);
	InitCurrentMP(1.0f);
	InitMaxMP(1.0f);
	InitMaxLevel(1.0f);
}

void UMageAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	UMageUIComponent* MageUIComponent = CachedPawnUIInterface->GetMageUIComponent();

	if (Data.EvaluatedData.Attribute == GetCurrentMPAttribute())
	{
		float NewMP = FMath::Clamp(GetCurrentMP(), 0.0f, GetMaxMP());
		SetCurrentMP(NewMP);

		MageUIComponent->OnChangeCurrentMP.Broadcast(GetCurrentMP() / GetMaxMP());
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMPAttribute())
	{
		SetMaxMP(FMath::Max(GetMaxMP(), 0.0f));

		MageUIComponent->OnSettingMaxMana.Broadcast(GetMaxMP());
	}
	else if (Data.EvaluatedData.Attribute == GetHPLevelAttribute())
	{
		float NewLevel = FMath::Clamp(GetHPLevel(), 0, GetMaxLevel());
		SetHPLevel(NewLevel);
	}
	else if (Data.EvaluatedData.Attribute == GetAttackLevelAttribute())
	{
		float NewLevel = FMath::Clamp(GetAttackLevel(), 0, GetMaxLevel());
		SetAttackLevel(NewLevel);
	}
	else if (Data.EvaluatedData.Attribute == GetMaxLevelAttribute())
	{
		float NewMaxLevel = UMageAndSeekerFunctionLibrary::GetCurrentCycle(GetOwningActor()) * 10;
		float Cap = FMath::Clamp(NewMaxLevel, 0, 30);
		SetMaxLevel(Cap);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Interface/PawnUIInterface.h"
#include "Component/UI/PawnUIComponent.h"
#include "Character/BaseCharacter.h"

#include "DebugHelper.h"

UMASBaseAttributeSet::UMASBaseAttributeSet()
{
	InitCurrentHP(1.0f);
	InitMaxHP(1.0f);
	InitAttackPower(1.0f);
	InitDefensivePower(1.0f);
}

void UMASBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (!CachedPawnUIInterface.IsValid())
    {
        CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
    }
    checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorLabel());

    UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

    if (Data.EvaluatedData.Attribute == GetCurrentHPAttribute())
    {
        float NewHP = FMath::Clamp(GetCurrentHP(), 0.0f, GetMaxHP());
        SetCurrentHP(NewHP);

        PawnUIComponent->OnChangedHP.Broadcast(GetCurrentHP() / GetMaxHP(), GetMaxHP());

        if (NewHP <= 0.0f)
        {
            ABaseCharacter* Character = Cast<ABaseCharacter>(Data.Target.GetAvatarActor());
            Character->CharacterDied();
        }
    }
    else if (Data.EvaluatedData.Attribute == GetMaxHPAttribute())
    {
        PawnUIComponent->OnChangedHP.Broadcast(GetCurrentHP() / GetMaxHP(), GetMaxHP());
    }

    else if (Data.EvaluatedData.Attribute == GetAttackPowerAttribute())
    {
        SetAttackPower(FMath::Max(GetAttackPower(), 0.0f));
    }
    else if (Data.EvaluatedData.Attribute == GetDefensivePowerAttribute())
    {
        SetDefensivePower(FMath::Max(GetDefensivePower(), 0.0f));
    }
}
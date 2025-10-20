// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/ArtifactAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Interface/PawnUIInterface.h"
#include "Component/UI/PawnUIComponent.h"
#include "Component/UI/MageUIComponent.h"


UArtifactAttributeSet::UArtifactAttributeSet()
{
	InitCurrentAP(0.0f);
	InitMaxAP(100.0f);
	InitAPChargePerHit(1.0f);
}

void UArtifactAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    if (!CachedPawnUIInterface.IsValid())
    {
        CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
    }
    checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorLabel());

    UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
    UMageUIComponent* MageUIComponent = CachedPawnUIInterface->GetMageUIComponent();

    if (Data.EvaluatedData.Attribute == GetCurrentAPAttribute())
    {
        float NewAP = FMath::Clamp(GetCurrentAP(), 0.0f, GetMaxAP());
        SetCurrentAP(NewAP);

        MageUIComponent->OnChangeCurrentAP.Broadcast(GetCurrentAP() / GetMaxAP());
    }
    else if (Data.EvaluatedData.Attribute == GetMaxAPAttribute())
    {
        SetMaxAP(FMath::Max(GetMaxAP(), 1.0f));
    }
    else if (Data.EvaluatedData.Attribute == GetAPChargePerHitAttribute())
    {
        SetAPChargePerHit(FMath::Max(GetAPChargePerHit(), 1.0f));
    }
}
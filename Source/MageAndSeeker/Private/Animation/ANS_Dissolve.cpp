// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ANS_Dissolve.h"

void UANS_Dissolve::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ElapsedTime = 0.f;
	Duration = FMath::Max(TotalDuration, KINDA_SMALL_NUMBER);

	MeshComp->SetScalarParameterValueOnMaterials("Dissolve", 0.0f);
}

void UANS_Dissolve::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	ElapsedTime += FrameDeltaTime * DissolveSpeed;
	float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);

	MeshComp->SetScalarParameterValueOnMaterials("Dissolve", Alpha);
}

void UANS_Dissolve::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	MeshComp->SetScalarParameterValueOnMaterials("Dissolve", 1.0f);
}
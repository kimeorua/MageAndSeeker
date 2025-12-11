// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "Component/Combat/Interface/CombatInterface.h"
#include "CombatComponent.generated.h"

UCLASS()
class MAGEANDSEEKER_API UCombatComponent : public UPawnExtensionComponent, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	virtual void RegisterWeapons_Implementation();
};

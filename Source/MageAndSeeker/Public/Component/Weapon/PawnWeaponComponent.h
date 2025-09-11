// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "PawnWeaponComponent.generated.h"

class ABaseWeapon;

UCLASS()
class MAGEANDSEEKER_API UPawnWeaponComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void RegisterWeapon(TArray<ABaseWeapon*>WeaponsToRegister);

};

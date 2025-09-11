// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Weapon/PawnWeaponComponent.h"
#include "Type/MageAndSeekerEnum.h"
#include "MageWeaponComponent.generated.h"

class ABaseWeapon;
class ASkeletalWeapon;
class AStaticWeapon;

UCLASS()
class MAGEANDSEEKER_API UMageWeaponComponent : public UPawnWeaponComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mage Weapon", meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponType, ABaseWeapon*>EquipedWeapons;

public:
	virtual void RegisterWeapon(TArray<ABaseWeapon*> WeaponsToRegister) override;
	
	UFUNCTION(BlueprintPure)
	AStaticWeapon* GetStaff() const;

	UFUNCTION(BlueprintPure)
	ASkeletalWeapon* GetBook() const;
};

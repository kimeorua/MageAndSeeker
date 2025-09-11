// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/MageAndSeekerEnum.h"
#include "BaseWeapon.generated.h"

class UMeshComponent;
class UMageWeaponComponent;

UCLASS(Abstract, NotBlueprintable)
class MAGEANDSEEKER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Mesh")
	UMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Type")
	EWeaponType WeaponType;
};
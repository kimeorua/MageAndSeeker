// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UMeshComponent;

UCLASS(Abstract, NotBlueprintable)
class MAGEANDSEEKER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Mesh")
	UMeshComponent* WeaponMesh;
};
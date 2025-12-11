// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/WeaponBase.h"
#include "EnemyWeapon.generated.h"

class UBoxComponent;

UCLASS()
class MAGEANDSEEKER_API AEnemyWeapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AEnemyWeapon();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
};
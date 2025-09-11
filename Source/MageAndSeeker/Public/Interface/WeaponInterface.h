// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

class UPawnWeaponComponent;
class UMageWeaponComponent;
class UMonsterWeaponComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGEANDSEEKER_API IWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPawnWeaponComponent* GetPawnWeaponComponent() const = 0;
	virtual UMageWeaponComponent* GetMageWeaponComponent() const;
	virtual UMonsterWeaponComponent* GetMonsterWeaponComponent() const;
};

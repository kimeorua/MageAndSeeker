// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/PawnUIInterface.h"
#include "Interface/WeaponInterface.h"
#include "BaseCharacter.generated.h"

class UMASAbilitySystemComponent;
class UMASBaseAttributeSet;
class UDataAsset_StartUp;

UCLASS()
class MAGEANDSEEKER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnUIInterface, public IWeaponInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	FORCEINLINE UMASAbilitySystemComponent* GetMASAbilitySystemComponent() const { return MASAbilitySystemComponent; }
	FORCEINLINE UMASBaseAttributeSet* GetMASBaseAttributeSet() const { return MASBaseAttributeSet; }

	// ~Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~End IAbilitySystemInterface

	UFUNCTION(BlueprintCallable)
	void InitCharacterStatAndAbility();

protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	// ~ Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	// ~ End IPawnUIInterface

	// ~ Begin IWeaponInterface
	virtual UPawnWeaponComponent* GetPawnWeaponComponent() const override;
	// ~ End IWeaponInterface

	virtual void CreateUIAndAdd();

#pragma region AbilitySystem

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMASAbilitySystemComponent* MASAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMASBaseAttributeSet* MASBaseAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Data")
	TSoftObjectPtr<UDataAsset_StartUp> CharacterStartUpData;

#pragma endregion
};

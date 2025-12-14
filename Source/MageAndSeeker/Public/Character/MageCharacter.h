// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "MageCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UMageAttributeSet;
class UArtifactAttributeSet;
class UMagicBookAttributeSet;
class AActivatedProps;
class UMageCombatComponent;
class UMageRuneComponent;
class UMageUIComponent;
class USaveLoadComponent;

UCLASS()
class MAGEANDSEEKER_API AMageCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMageCharacter();

	FORCEINLINE UMageAttributeSet* GetMageAttributeSet() const { return MageAttributeSet; }
	FORCEINLINE UArtifactAttributeSet* GetArtifactAttributeSet() const { return ArtifactAttributeSet; }
	FORCEINLINE UMageCombatComponent* GetMageCombatComponent() const { return MageCombatComponent; }
	FORCEINLINE UMageUIComponent* GetMageUIComponent() const { return MageUIComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMageAttributeSet* MageAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UArtifactAttributeSet* ArtifactAttributeSet;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Data Asset", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* DataAsset_InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMageCombatComponent* MageCombatComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMageRuneComponent* MageRuneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMageUIComponent* MageUIComponent;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputRelased(FGameplayTag InInputTag);

	void MageInit();
	virtual void InitCharacterStatAndAbility() override;
};
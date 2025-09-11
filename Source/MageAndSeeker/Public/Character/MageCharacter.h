// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MageCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UMageAttributeSet;
class UArtifactAttributeSet;
class UMageUIComponent;
class UMageWeaponComponent;

UCLASS()
class MAGEANDSEEKER_API AMageCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMageCharacter();

	FORCEINLINE UMageAttributeSet* GetMageAttributeSet() const { return MageAttributeSet; }
	FORCEINLINE UArtifactAttributeSet* GetArtifactAttributeSet() const { return ArtifactAttributeSet; }

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Component", meta = (AllowPrivateAccess = "true"))
	UMageUIComponent* MageUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Component", meta = (AllowPrivateAccess = "true"))
	UMageWeaponComponent* MageWeaponComponent;

#pragma endregion

#pragma region Input

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Interactive();

#pragma endregion

#pragma region Values

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Data Asset", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* DataAsset_InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Trace | Interaction", meta = (AllowPrivateAccess = "true"))
	bool bIsTraceShow = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

#pragma endregion

protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;

	// ~ Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UMageUIComponent* GetMageUIComponent() const override;
	// ~ End IPawnUIInterface

	// ~ Begin IPawnUIInterface
	virtual UPawnWeaponComponent* GetPawnWeaponComponent() const override;
	virtual UMageWeaponComponent* GetMageWeaponComponent() const override;
	// ~ End IPawnUIInterface

	virtual void CreateUIAndAdd() override; 

#pragma region AbilitySystem

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMageAttributeSet* MageAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UArtifactAttributeSet* ArtifactAttributeSet;

#pragma endregion
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MageCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;

UCLASS()
class MAGEANDSEEKER_API AMageCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMageCharacter();

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
#pragma endregion

#pragma region Input

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

#pragma endregion

#pragma region Values

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Data Asset", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* DataAsset_InputConfig;

#pragma endregion

protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
};

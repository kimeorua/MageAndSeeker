// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponent.h"
#include "GameplayEffectTypes.h"
#include "UIComponent.generated.h"

class UCharacterHUD;

UCLASS()
class MAGEANDSEEKER_API UUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	virtual void InitCharacterUI(ABaseCharacter* Owenr);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UCharacterHUD* HUD;

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCharacterHUD> CharacterHUDClass;

	void OnCurrentHPChanged(const FOnAttributeChangeData& Data);

	void OnMaxHPChanged(const FOnAttributeChangeData& Data);
};

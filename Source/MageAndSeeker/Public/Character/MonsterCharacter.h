// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Type/Enums/GamePlayEnums.h"
#include "MonsterCharacter.generated.h"

class UMonsterAttributeSet;
class UMonsterCombatComponent;
class UMonsterUIComponent;
class UWidgetComponent;

UCLASS()
class MAGEANDSEEKER_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMonsterCharacter();

	FORCEINLINE void SetMonsterLV(const int32 LV = 1) { MonsterLV = LV; }

	FORCEINLINE UMonsterUIComponent* GetMonsterUIComponent() const { return MonsterUIComponent; }

	void SettingMonsterColor(EDungeonElemental DungeonElemental);

	UFUNCTION(BlueprintCallable)
	virtual void OnCharacterDied() override;

	UFUNCTION(BlueprintPure)
	UAnimMontage* GetMonsterDiedAnimation() const;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMonsterAttributeSet* MonsterAttributeSet;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMonsterCombatComponent* MonsterCombatComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMonsterUIComponent* MonsterUIComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HPBarWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HPBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DieadMontage;

	virtual void InitCharacterStatAndAbility() override;

	int32 MonsterLV;
};